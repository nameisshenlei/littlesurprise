#include "gstTestPlayer.h"
#include "gstMainPreview.h"
#include "gstRtmpPushBin.h"

nemoGstTestPlayer::nemoGstTestPlayer()
: m_elmtVideoFakeSink(nullptr)
{

}

nemoGstTestPlayer::~nemoGstTestPlayer()
{
	if (m_isLinkRtmpPush)
	{
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoFakeSink);
	}
	else
	{
		m_elmtVideoFakeSink = nullptr;
	}
}

int nemoGstTestPlayer::initPlayer(GstClock* mainClock, nemoGstBasePlayerCallback* cb)
{
	if (initBasePlayer(cb) != 0)
		return -1;

	m_padMultiQueueVideoPreview = nullptr;
	m_padMultiQueueAudioPreview = nullptr;
	m_padAudioTeeRender = nullptr;
	m_padAudioTeeAppSink = nullptr;
	m_padVideoTeeRender = nullptr;
	m_padVideoTeeAppSink = nullptr;

	m_elmtVideoFakeSink = nullptr;

	GstElement* elmtVideoTestSrc = nullptr;
	GstElement* elmtVideoTee = nullptr;
	GstElement* elmtAudioTestSrc = nullptr;
	GstElement* elmtAudioTee = nullptr;
	GstElement* elmtMediaMultiQueue = nullptr;

	// video test src
	elmtVideoTestSrc = gst_element_factory_make("videotestsrc", NEMOGST_ELEMENT_NAME_VIDEO_TESTSRC);
	// video tee
	elmtVideoTee = gst_element_factory_make("tee", NEMOGST_ELEMENT_NAME_VIDEO_TEE);
	// video fake sink
	m_elmtVideoFakeSink = gst_element_factory_make("appsink", NEMOGST_ELEMENT_NAME_VIDEO_FAKE_SINK);
	// audio test src
	elmtAudioTestSrc = gst_element_factory_make("audiotestsrc", NEMOGST_ELEMENT_NAME_AUDIO_TESTSRC);
	// audio tee
	elmtAudioTee = gst_element_factory_make("tee", NEMOGST_ELEMENT_NAME_AUDIO_TEE);
	// media multi queue
	elmtMediaMultiQueue = gst_element_factory_make("multiqueue", NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);

	if (!elmtVideoTestSrc || !elmtVideoTee || ! m_elmtVideoFakeSink
		|| !elmtAudioTestSrc || !elmtAudioTee || !elmtMediaMultiQueue)
	{
		goto INIT_FAILED;
	}

	// create a new pipeline
	m_elmtPipeline = gst_pipeline_new(nullptr);
	if (!m_elmtPipeline)
	{
		goto INIT_FAILED;
	}
	gst_pipeline_set_clock(GST_PIPELINE(m_elmtPipeline), mainClock);

	// add all element in the pipeline
	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, elmtVideoTestSrc
		, elmtVideoTee
		, m_elmtVideoFakeSink
		, elmtAudioTestSrc
		, elmtAudioTee
		, elmtMediaMultiQueue
		, nullptr);

	// audio test
	g_object_set(elmtAudioTestSrc, "wave", 12, nullptr);
	g_object_set(elmtAudioTestSrc, "volume", 0.1, nullptr);
	g_object_set(elmtAudioTestSrc, "is-live", true, nullptr);

	// video-tee
	{
		GstPadTemplate *video_tee_src_pad_template;
		// request a pad for video render from tee
		video_tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(elmtVideoTee), "src_%u");
		m_padVideoTeeRender = gst_element_request_pad(elmtVideoTee, video_tee_src_pad_template, nullptr, nullptr);
		m_padVideoTeeAppSink = gst_element_request_pad(elmtVideoTee, video_tee_src_pad_template, nullptr, nullptr);
	}
	// audio-tee
	{
		GstPadTemplate *audio_tee_src_pad_template;
		// request a pad for video render from tee
		audio_tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(elmtAudioTee), "src_%u");
		m_padAudioTeeRender = gst_element_request_pad(elmtAudioTee, audio_tee_src_pad_template, nullptr, nullptr);
		m_padAudioTeeAppSink = gst_element_request_pad(elmtAudioTee, audio_tee_src_pad_template, nullptr, nullptr);
	}
	// multi-queue
	{
		// sink_1
		m_padMultiQueueVideoPreview = gst_element_get_request_pad(elmtMediaMultiQueue, "sink_1");
		// sink_2
		m_padMultiQueueAudioPreview = gst_element_get_request_pad(elmtMediaMultiQueue, "sink_2");
	}

	// link video test-src and video-tee
	if (!gst_element_link(elmtVideoTestSrc, elmtVideoTee))
	{
		goto INIT_FAILED;
	}
	// link video tee and video fake sink
	{
		GstPad* pad_video_fake_sink = gst_element_get_static_pad(m_elmtVideoFakeSink, "sink");
		if (gst_pad_link(m_padVideoTeeAppSink, pad_video_fake_sink) != GST_PAD_LINK_OK)
		{
			goto INIT_FAILED;
		}
		gst_object_unref(pad_video_fake_sink);
	}

	// link video tee and multi-queue
	if (gst_pad_link(m_padVideoTeeRender, m_padMultiQueueVideoPreview) != GST_PAD_LINK_OK)
	{
		goto INIT_FAILED;
	}

	// link audio test-src and audio tee
	if (!gst_element_link(elmtAudioTestSrc, elmtAudioTee))
	{
		goto INIT_FAILED;
	}

	if (link_audio_convert_elemets() != 0)
	{
		goto INIT_FAILED;
	}

	// link audio tee and multi-queue
	if (gst_pad_link(m_padAudioTeeRender, m_padMultiQueueAudioPreview) != GST_PAD_LINK_OK)
	{
		goto INIT_FAILED;
	}

	// set pipeline's bus
	GstBus* bus = gst_element_get_bus(m_elmtPipeline);
	setBusSyncCallback(bus);

	return 0;

INIT_FAILED:
	if (m_padVideoTeeRender)
	{
		gst_element_release_request_pad(elmtVideoTee, m_padVideoTeeRender);
		m_padVideoTeeRender = nullptr;
	}
	if (m_padVideoTeeAppSink)
	{
		gst_element_release_request_pad(elmtVideoTee, m_padVideoTeeAppSink);
		m_padVideoTeeAppSink = nullptr;
	}
	if (m_padAudioTeeRender)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeRender);
		m_padAudioTeeRender = nullptr;
	}
	if (m_padAudioTeeAppSink)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeAppSink);
		m_padAudioTeeAppSink = nullptr;
	}
	if (m_padMultiQueueVideoPreview)
	{
		gst_element_release_request_pad(elmtMediaMultiQueue, m_padMultiQueueVideoPreview);
		m_padMultiQueueVideoPreview = nullptr;
	}
	if (m_padMultiQueueAudioPreview)
	{
		gst_element_release_request_pad(elmtMediaMultiQueue, m_padMultiQueueAudioPreview);
		m_padMultiQueueAudioPreview = nullptr;
	}

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}
	else
	{
		gst_object_unref(elmtVideoTestSrc);
		gst_object_unref(elmtVideoTee);
		gst_object_unref(m_elmtVideoFakeSink);
		gst_object_unref(elmtAudioTestSrc);
		gst_object_unref(elmtAudioTee);
		gst_object_unref(elmtMediaMultiQueue);
	}

	return -1;
}

int nemoGstTestPlayer::play()
{
	GstStateChangeReturn stateRet = gst_element_set_state(m_elmtPipeline, GST_STATE_PLAYING);
	if (stateRet != GST_STATE_CHANGE_SUCCESS && stateRet != GST_STATE_CHANGE_ASYNC)
	{
		return -1;
	}

	return 0;
}

void nemoGstTestPlayer::stop()
{
	gst_element_set_state(m_elmtPipeline, GST_STATE_NULL);

	// release pads of video tee
	GstElement* elmtVideoTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_VIDEO_TEE);
	if (m_padVideoTeeRender)
	{
		gst_element_release_request_pad(elmtVideoTee, m_padVideoTeeRender);
		m_padVideoTeeRender = nullptr;
	}
	if (m_padVideoTeeAppSink)
	{
		gst_element_release_request_pad(elmtVideoTee, m_padVideoTeeAppSink);
		m_padVideoTeeAppSink = nullptr;
	}
	gst_object_unref(elmtVideoTee);

	// release pads of audio tee
	GstElement* elmtAudioTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_AUDIO_TEE);
	if (m_padAudioTeeAppSink)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeAppSink);
		m_padAudioTeeAppSink = nullptr;
	}
	if (m_padAudioTeeRender)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeRender);
		m_padAudioTeeRender = nullptr;
	}
	gst_object_unref(elmtAudioTee);

	// release pads of media render queue
	GstElement* elmtMediaRenderMultiQueue = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);
	if (m_padMultiQueueVideoPreview)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueVideoPreview);
		m_padMultiQueueVideoPreview = nullptr;
	}
	if (m_padMultiQueueAudioPreview)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueAudioPreview);
		m_padMultiQueueAudioPreview = nullptr;
	}
	gst_object_unref(elmtMediaRenderMultiQueue);

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}
}

void nemoGstTestPlayer::on_link_main_preview(GstPad* pad_video_preview, GstPad* pad_audio_convert)
{
	GstElement* elmtMultiQueue = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);
	// link video main preview
	{
		GstPad* pad_video_multi_queue = gst_element_get_static_pad(elmtMultiQueue, "src_1");

		if (gst_pad_link(pad_video_multi_queue, pad_video_preview) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_video_multi_queue);
	}
	// link audio convert
	{
		GstPad* pad_audio_multi_queue = gst_element_get_static_pad(elmtMultiQueue, "src_2");

		if (gst_pad_link(pad_audio_multi_queue, pad_audio_convert) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_audio_multi_queue);
	}

	gst_object_unref(elmtMultiQueue);
}

void nemoGstTestPlayer::on_broken_main_preview()
{

}

void nemoGstTestPlayer::on_link_rtmp_push(nemoGstRtmpPush* pRtmp, GstPad* pad_video_appsink_queue)
{
	gst_object_ref(m_elmtVideoFakeSink);

	gst_bin_remove_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoFakeSink
		, nullptr);

	// link video
	if (gst_pad_link(m_padVideoTeeAppSink, pad_video_appsink_queue) != GST_PAD_LINK_OK)
	{
		return;
	}
}

void nemoGstTestPlayer::on_broken_rtmp_push()
{
	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoFakeSink
		, nullptr);

	if (!gst_element_sync_state_with_parent(m_elmtVideoFakeSink))
	{
		return;
	}

	// link video tee and video fake sink
	{
		GstPad* pad_video_fake_sink = gst_element_get_static_pad(m_elmtVideoFakeSink, "sink");
		if (gst_pad_link(m_padVideoTeeAppSink, pad_video_fake_sink) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_video_fake_sink);
	}
}

