#include "gstUriPlayer.h"
#include "gstHelpFunctions.h"
#include "gstRtmpPushBin.h"

//////////////////////////////////////////////////////////////////////////

nemoGstUriPlayer::nemoGstUriPlayer()
{

}

nemoGstUriPlayer::~nemoGstUriPlayer()
{

}

int nemoGstUriPlayer::playerInit(GstClock* mainClock, nemoGstBasePlayerCallback* cb, String uri, void* win_handle)
{
	if (initBasePlayer(cb) != 0)
		return -1;

	int ret = 0;

	m_haveAudio = false;
	m_haveVideo = false;

	m_elmtPipeline = nullptr;
	m_padVideoTeeRender = nullptr;
	m_padVideoTeeAppSink = nullptr;
	m_padVideoRenderTee1 = nullptr;
	m_padVideoRenderTee2 = nullptr;
	m_padMultiQueueVideoPreview = nullptr;
	m_padMultiQueueVideoRender = nullptr;
	m_padMultiQueueAudioPreview = nullptr;
	m_padAudioTeeRender = nullptr; 
	m_padAudioTeeAppSink = nullptr;
	m_padAudioTeeSpaceScope = nullptr;

	String fileUri;

	//gst element;
	GstElement*	elmtUriDecodeBin = nullptr;
	GstElement*	elmtVideoTee = nullptr;
	GstElement*	elmtVideoQueue = nullptr;
	GstElement* elmtVideoConvert = nullptr;
	GstElement* elmtVideoRenderTee = nullptr;
	GstElement* elmtVideoRenderD3D = nullptr;
	GstElement*	elmtAudioTee = nullptr;
	GstElement* elmtMediaRenderMultiQueue = nullptr;
	GstElement* elmtAudioSpaceScope = nullptr;

	GstBus* bus = nullptr;

	// uri decode bin
	elmtUriDecodeBin = gst_element_factory_make("uridecodebin", NEMOGST_ELEMENT_NAME_URIDECODEBIN);
	// video tee
	elmtVideoTee = gst_element_factory_make("tee", NEMOGST_ELEMENT_NAME_VIDEO_TEE);
	// video queue
	elmtVideoQueue = gst_element_factory_make("queue", NEMOGST_ELEMENT_NAME_VIDEO_QUEUE);
	// video convert
	elmtVideoConvert = gst_element_factory_make("videoconvert", NEMOGST_ELEMENT_NAME_VIDEO_CONVERT);
	// video render tee
	elmtVideoRenderTee = gst_element_factory_make("tee", NEMOGST_ELEMENT_NAME_VIDEO_RENDER_TEE);
	// video render direct3d
	elmtVideoRenderD3D = gst_element_factory_make("d3dvideosink", NEMOGST_ELEMENT_NAME_VIDEO_RENDER_D3D);
	// audio tee
	elmtAudioTee = gst_element_factory_make("tee", NEMOGST_ELEMENT_NAME_AUDIO_TEE);
	// audio space scope
	elmtAudioSpaceScope = gst_element_factory_make("spacescope", NEMOGST_ELEMENT_NAME_AUDIO_SPACESCOPE);
	// media render multi queue
	elmtMediaRenderMultiQueue = gst_element_factory_make("multiqueue", NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);

	// check all elmemt
	if (!elmtUriDecodeBin || !elmtVideoTee || !elmtVideoQueue || !elmtVideoConvert \
		|| !elmtVideoRenderTee || !elmtVideoRenderD3D || !elmtAudioTee || !elmtMediaRenderMultiQueue \
		|| !elmtAudioSpaceScope)
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
		, elmtUriDecodeBin
		, elmtVideoTee
		, elmtVideoQueue
		, elmtVideoConvert
		, elmtVideoRenderTee
		, elmtVideoRenderD3D
		, elmtAudioTee
		, elmtMediaRenderMultiQueue
		, elmtAudioSpaceScope
		, nullptr);


	// set uriDecodeBin's parameters;
	// set uri
	if (!uri.startsWith("rtmp://"))
	{
		if (!uri.startsWith("file:///"))
		{
			fileUri = L"file:///";
		}
	}
	fileUri += uri;
	g_object_set(elmtUriDecodeBin, "uri", fileUri.toRawUTF8(), nullptr);
	// set pad signal
	// no-more-pads
	g_signal_connect(elmtUriDecodeBin, "no-more-pads", G_CALLBACK(nemogst_signal_uri_player_uridecodebin_no_more_pads), this);
	// added a new pad
	g_signal_connect(elmtUriDecodeBin, "pad-added", G_CALLBACK(nemogst_signal_uri_player_uridecodebin_pad_added), this);
	// removed a old pad
	g_signal_connect(elmtUriDecodeBin, "pad-removed", G_CALLBACK(nemogst_signal_uri_player_uridecodebin_pad_removed), this);

	// set videoRenderD3D's windows handle
	// video render windows handle
// 	g_object_set(elmtVideoRenderD3D, "sync", true, false);
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(elmtVideoRenderD3D), (guintptr)win_handle);

	// set pipeline's bus
	bus = gst_element_get_bus(m_elmtPipeline);
	setBusSyncCallback(bus);

	// video-tee
	{
		GstPadTemplate *video_tee_src_pad_template;
		// request a pad for video render from tee
		video_tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(elmtVideoTee), "src_%u");
		m_padVideoTeeRender = gst_element_request_pad(elmtVideoTee, video_tee_src_pad_template, nullptr, nullptr);
		m_padVideoTeeAppSink = gst_element_request_pad(elmtVideoTee, video_tee_src_pad_template, nullptr, nullptr);
	}
	// video-render-tee
	{
		GstPadTemplate *video_render_tee_src_pad_template;
		// request a pad for video render from tee
		video_render_tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(elmtVideoRenderTee), "src_%u");
		m_padVideoRenderTee1 = gst_element_request_pad(elmtVideoRenderTee, video_render_tee_src_pad_template, nullptr, nullptr);
		m_padVideoRenderTee2 = gst_element_request_pad(elmtVideoRenderTee, video_render_tee_src_pad_template, nullptr, nullptr);
	}
	// audio-tee
	{
		GstPadTemplate *audio_tee_src_pad_template;
		// request a pad for video render from tee
		audio_tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(elmtAudioTee), "src_%u");
		m_padAudioTeeRender = gst_element_request_pad(elmtAudioTee, audio_tee_src_pad_template, nullptr, nullptr);
		m_padAudioTeeAppSink = gst_element_request_pad(elmtAudioTee, audio_tee_src_pad_template, nullptr, nullptr);
		m_padAudioTeeSpaceScope = gst_element_request_pad(elmtAudioTee, audio_tee_src_pad_template, nullptr, nullptr);
	}
	// multi-queue
	{
		// sink_1
		m_padMultiQueueVideoRender = gst_element_get_request_pad(elmtMediaRenderMultiQueue, "sink_1");
		// sink_2
		m_padMultiQueueVideoPreview = gst_element_get_request_pad(elmtMediaRenderMultiQueue, "sink_2");
		// sink_3
		m_padMultiQueueAudioPreview = gst_element_get_request_pad(elmtMediaRenderMultiQueue, "sink_3");
	}
	//
	if (init_link_video_process(elmtVideoQueue, elmtVideoConvert, elmtVideoRenderTee, elmtMediaRenderMultiQueue, elmtVideoRenderD3D) != 0)
	{
		goto INIT_FAILED;
	}

	if (init_link_audio_process(elmtAudioSpaceScope) != 0)
	{
		goto INIT_FAILED;
	}

	if (link_audio_convert_elemets() != 0)
	{
		goto INIT_FAILED;
	}

	return ret;

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
	if (m_padVideoRenderTee1)
	{
		gst_element_release_request_pad(elmtVideoRenderTee, m_padVideoRenderTee1);
		m_padVideoRenderTee1 = nullptr;
	}
	if (m_padVideoRenderTee2)
	{
		gst_element_release_request_pad(elmtVideoRenderTee, m_padVideoRenderTee2);
		m_padVideoRenderTee2 = nullptr;
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
	if (m_padAudioTeeSpaceScope)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeSpaceScope);
		m_padAudioTeeSpaceScope = nullptr;
	}

	if (m_padMultiQueueVideoRender)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueVideoRender);
		m_padMultiQueueVideoRender = nullptr;
	}
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

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}
	else
	{
		gst_object_unref(elmtUriDecodeBin);
		gst_object_unref(elmtVideoTee);
		gst_object_unref(elmtVideoQueue);
		gst_object_unref(elmtVideoConvert);
		gst_object_unref(elmtVideoRenderTee);
		gst_object_unref(elmtVideoRenderD3D);
		gst_object_unref(elmtAudioTee);
		gst_object_unref(elmtMediaRenderMultiQueue);
		gst_object_unref(elmtAudioSpaceScope);
	}

	return -1;
}

int nemoGstUriPlayer::play(bool needProcess)
{
	GstStateChangeReturn stateRet = gst_element_set_state(m_elmtPipeline, GST_STATE_PLAYING);
	if (stateRet != GST_STATE_CHANGE_SUCCESS && stateRet != GST_STATE_CHANGE_ASYNC)
	{
		return -1;
	}
#ifdef _DEBUG
	GST_DEBUG_BIN_TO_DOT_FILE((GstBin *)m_elmtPipeline, GST_DEBUG_GRAPH_SHOW_ALL, "uriPlayer");
#endif

	if (needProcess)
	{
		startTimer(500);
	}
	return 0;
}

void nemoGstUriPlayer::stop()
{
	stopTimer();

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

	// release pads of video render tee
	GstElement* elmtVideoRenderTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_VIDEO_RENDER_TEE);
	if (m_padVideoRenderTee1)
	{
		gst_element_release_request_pad(elmtVideoRenderTee, m_padVideoRenderTee1);
		gst_object_unref(m_padVideoRenderTee1);
		m_padVideoRenderTee1 = nullptr;
	}
	if (m_padVideoRenderTee2)
	{
		gst_element_release_request_pad(elmtVideoRenderTee, m_padVideoRenderTee2);
		gst_object_unref(m_padVideoRenderTee2);
		m_padVideoRenderTee2 = nullptr;
	}
	gst_object_unref(elmtVideoRenderTee);

	// release pads of audio tee
	GstElement* elmtAudioTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_AUDIO_TEE);
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
	if (m_padAudioTeeSpaceScope)
	{
		gst_element_release_request_pad(elmtAudioTee, m_padAudioTeeSpaceScope);
		m_padAudioTeeSpaceScope = nullptr;
	}
	gst_object_unref(elmtAudioTee);

	// release pads of media render queue
	GstElement* elmtMediaRenderMultiQueue = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);
	if (m_padMultiQueueVideoRender)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueVideoRender);
		gst_object_unref(m_padMultiQueueVideoRender);
		m_padMultiQueueVideoRender = nullptr;
	}
	if (m_padMultiQueueVideoPreview)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueVideoPreview);
		gst_object_unref(m_padMultiQueueVideoPreview);
		m_padMultiQueueVideoPreview = nullptr;
	}
	if (m_padMultiQueueAudioPreview)
	{
		gst_element_release_request_pad(elmtMediaRenderMultiQueue, m_padMultiQueueAudioPreview);
		gst_object_unref(m_padMultiQueueAudioPreview);
		m_padMultiQueueAudioPreview = nullptr;
	}
	gst_object_unref(elmtMediaRenderMultiQueue);

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}
}

void nemoGstUriPlayer::seek(gint64 s)
{
	gst_element_seek_simple(m_elmtPipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, s);
}

void nemoGstUriPlayer::seekForward()
{
	bool needTimer = isTimerRunning();
	if (needTimer)
	{
		stopTimer();
	}

	gint64 c = 0;
	if (gst_element_query_position(m_elmtPipeline, GST_FORMAT_TIME, &c))
	{
		c += 30000000000;
		gst_element_seek_simple(m_elmtPipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, c);
	}

	if (needTimer)
	{
		startTimer(500);
	}
}

void nemoGstUriPlayer::seekBack()
{
	bool needTimer = isTimerRunning();
	if (needTimer)
	{
		stopTimer();
	}

	gint64 c = 0;
	if (gst_element_query_position(m_elmtPipeline, GST_FORMAT_TIME, &c))
	{
		c -= 30000000000;
		if (c < 0) c = 0;
		gst_element_seek_simple(m_elmtPipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, c);
	}

	if (needTimer)
	{
		startTimer(500);
	}

}

void nemoGstUriPlayer::on_link_main_preview(GstPad* pad_video_preview, GstPad* pad_audio_convert)
{
	GstElement* elmtMultiQueue = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_MEDIA_MULTIQUEUE);
	// link video main preview
	{
		GstPad* pad_video_multi_queue = gst_element_get_static_pad(elmtMultiQueue, "src_2");

		if (gst_pad_link(pad_video_multi_queue, pad_video_preview) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_video_multi_queue);
	}
	// link audio convert and multi queue
	{
		GstPad* pad_audio_multi_queue = gst_element_get_static_pad(elmtMultiQueue, "src_3");
		if (gst_pad_link(pad_audio_multi_queue, pad_audio_convert) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_audio_multi_queue);
	}

	gst_object_unref(elmtMultiQueue);
}

void nemoGstUriPlayer::on_broken_main_preview()
{

}

void nemoGstUriPlayer::on_link_rtmp_push(nemoGstRtmpPush* /*pRtmp*/, GstPad* pad_video_appsink_queue)
{
	// link video
	if (gst_pad_link(m_padVideoTeeAppSink, pad_video_appsink_queue) != GST_PAD_LINK_OK)
	{
		return;
	}
}

void nemoGstUriPlayer::on_broken_rtmp_push()
{

}

void nemoGstUriPlayer::timerCallback()
{
	gint64 d, c;
	if (!gst_element_query_position(m_elmtPipeline, GST_FORMAT_TIME, &c))
	{
		stopTimer();
		return;
	}

	if (!gst_element_query_duration(m_elmtPipeline, GST_FORMAT_TIME, &d))
	{
		stopTimer();
		return;
	}

	nemoGstBasePlayerProcessMessage* msg = new nemoGstBasePlayerProcessMessage(this, d, c);
	m_callback->postMessage(msg);
}

void nemoGstUriPlayer::callbackUriDecodeBinNoMorePads()
{
	// check pads
}

void nemoGstUriPlayer::callbackUriDecodeBinPadAdded(GstPad* new_pad)
{
	if (gstHelpPadIsVideo(new_pad))
	{
		// is video
		GstPad* pad_video_tee = nullptr;
		GstElement* elmtVideoTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_VIDEO_TEE);
		pad_video_tee = gst_element_get_static_pad(elmtVideoTee, "sink");

		// link uri-decode-bin and video-box;
		if (gst_pad_link(new_pad, pad_video_tee) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_video_tee);
		gst_object_unref(elmtVideoTee);

		// link uriDecodeBin and videoTee
		
	}
	else if (gstHelpPadIsAudio(new_pad))
	{
		// is audio
		GstPad* pad_audio_tee = nullptr;
		GstElement* elmtAudioTee = gst_bin_get_by_name(GST_BIN(m_elmtPipeline), NEMOGST_ELEMENT_NAME_AUDIO_TEE);
		pad_audio_tee = gst_element_get_static_pad(elmtAudioTee, "sink");

		// link uri-decode-bin and video-box;
		if (gst_pad_link(new_pad, pad_audio_tee) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(pad_audio_tee);
		gst_object_unref(elmtAudioTee);
	}
}

void nemoGstUriPlayer::callbackUriDecodeBinPadRemoved(GstPad* /*old_pad*/)
{

}

int nemoGstUriPlayer::init_link_video_process(
	GstElement*	elmtVideoQueue,
	GstElement* elmtVideoConvert,
	GstElement* elmtVideoRenderTee,
	GstElement* elmtMediaRenderMultiQueue,
	GstElement* elmtVideoRenderD3D)
{
	// video-tee
	{
		// get source pad from video queue
		GstPad* video_pad_queue;
		video_pad_queue = gst_element_get_static_pad(elmtVideoQueue, "sink");
		// link tee and video scale's pad
		if (gst_pad_link(m_padVideoTeeRender, video_pad_queue) != GST_PAD_LINK_OK)
		{
			return -1;
		}
		gst_object_unref(video_pad_queue);
	}

	// link video queue and convert

	if (!gst_element_link(elmtVideoQueue, elmtVideoConvert))
	{
		return -1;
	}

	// link video convert and video render tee
	if (!gst_element_link(elmtVideoConvert, elmtVideoRenderTee))
	{
		return -1;
	}

	// link video-render-tee' pad and multi-queue's pad
	if (gst_pad_link(m_padVideoRenderTee1, m_padMultiQueueVideoRender) != GST_PAD_LINK_OK)
	{
		return -1;
	}
	if (gst_pad_link(m_padVideoRenderTee2, m_padMultiQueueVideoPreview) != GST_PAD_LINK_OK)
	{
		return -1;
	}

	// link multi-queue and video render-d3d
	{
		GstPad* pad_multi_queue_video_render;
		pad_multi_queue_video_render = gst_element_get_static_pad(elmtMediaRenderMultiQueue, "src_1");
		GstPad* pad_video_render_d3d;
		pad_video_render_d3d = gst_element_get_static_pad(elmtVideoRenderD3D, "sink");

		if (gst_pad_link(pad_multi_queue_video_render, pad_video_render_d3d) != GST_PAD_LINK_OK)
		{
			return -1;
		}
		gst_object_unref(pad_multi_queue_video_render);
		gst_object_unref(pad_video_render_d3d);
	}

	return 0;
}

int nemoGstUriPlayer::init_link_audio_process(
	GstElement* /*elmtAudioSpaceScope*/)
{

	if (gst_pad_link(m_padAudioTeeRender, m_padMultiQueueAudioPreview) != GST_PAD_LINK_OK)
	{
		return -1;
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////
void nemogst_signal_uri_player_uridecodebin_no_more_pads(GstElement * /*gstelement*/, gpointer user_data)
{
	nemoGstUriPlayer* p = static_cast<nemoGstUriPlayer*>(user_data);
	if (p)
	{
		p->callbackUriDecodeBinNoMorePads();
	}

}

void nemogst_signal_uri_player_uridecodebin_pad_added(GstElement * /*gstelement*/, GstPad *new_pad, gpointer user_data)
{
	nemoGstUriPlayer* p = static_cast<nemoGstUriPlayer*>(user_data);
	if (p)
	{
		p->callbackUriDecodeBinPadAdded(new_pad);
	}
}

void nemogst_signal_uri_player_uridecodebin_pad_removed(GstElement * /*gstelement*/, GstPad *old_pad, gpointer user_data)
{
	nemoGstUriPlayer* p = static_cast<nemoGstUriPlayer*>(user_data);
	if (p)
	{
		p->callbackUriDecodeBinPadRemoved(old_pad);
	}
}
