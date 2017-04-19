#include "gstBasePlayer.h"
#include "gstRtmpPushBin.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// nemoGstBasePlayerMessage
nemoGstBasePlayerMessage::nemoGstBasePlayerMessage(nemoGstBasePlayer* p, gstMsgType msgType)
: m_msgType(msgType)
, m_player(p)
{

}

nemoGstBasePlayerMessage::~nemoGstBasePlayerMessage()
{

}

nemoGstBasePlayerMessage::gstMsgType nemoGstBasePlayerMessage::getMsgType()
{
	return m_msgType;
}

nemoGstBasePlayer* nemoGstBasePlayerMessage::getPlayer()
{
	return m_player;
}
//////////////////////////////////////////////////////////////////////////
// nemoGstBasePlayerProcessMessage
nemoGstBasePlayerProcessMessage::nemoGstBasePlayerProcessMessage(nemoGstBasePlayer* p, gint64 d, gint64 c)
: nemoGstBasePlayerMessage(p, nemoGstBasePlayerMessage::gstMsgTypeProcess)
, m_timeDuration(d)
, m_timeCurrent(c)
{

}
nemoGstBasePlayerProcessMessage::~nemoGstBasePlayerProcessMessage()
{

}

gint64 nemoGstBasePlayerProcessMessage::getDuration()
{
	return m_timeDuration;
}

gint64 nemoGstBasePlayerProcessMessage::getCurrent()
{
	return m_timeCurrent;
}
//////////////////////////////////////////////////////////////////////////
// nemoGstBasePlayerCallback

nemoGstBasePlayerCallback::nemoGstBasePlayerCallback()
{

}

nemoGstBasePlayerCallback::~nemoGstBasePlayerCallback()
{

}

void nemoGstBasePlayerCallback::handleMessage(const Message& message)
{
	nemoGstBasePlayerMessage* msg = dynamic_cast<nemoGstBasePlayerMessage*>((Message*)(&message));
	switch (msg->getMsgType())
	{
	case nemoGstBasePlayerMessage::gstMsgTypeError:
		onBasePlayerError(msg->getPlayer());
		break;
	case nemoGstBasePlayerMessage::gstMsgTypeEOS:
		onBasePlayerEOS(msg->getPlayer());
		break;
	case nemoGstBasePlayerMessage::gstMsgTypeRunning:
		onBasePlayerRunning(msg->getPlayer());
		break;
	case nemoGstBasePlayerMessage::gstMsgTypeProcess:
		nemoGstBasePlayerProcessMessage* processMsg = dynamic_cast<nemoGstBasePlayerProcessMessage*>(msg);
		onBasePlayerProcess(processMsg->getPlayer(), processMsg->getDuration(), processMsg->getCurrent());
		break;
	}
}


//////////////////////////////////////////////////////////////////////////

nemoGstBasePlayer::nemoGstBasePlayer()
: m_elmtPipeline(nullptr)
, m_callback(nullptr)
, m_isLinkMainPreview(false)
, m_isLinkRtmpPush(false)
, m_elmtVideoPreviewD3D(nullptr)
, m_elmtAudioConvert(nullptr)
, m_elmtAudioPreview(nullptr)
, m_elmtVideoAppSinkQueue(nullptr)
, m_elmtVideoAppSinkScale(nullptr)
, m_elmtVideoAppSinkRate(nullptr)
, m_elmtVideoAppSinkConvert(nullptr)
, m_elmtVideoAppSink(nullptr)
, m_elmtAudioAppSink(nullptr)
, m_padAudioTeeAppSink(nullptr)
, m_padVideoTeeAppSink(nullptr)
, m_padAudioTeeRender(nullptr)
, m_padVideoTeeRender(nullptr)
, m_padMultiQueueAudioPreview(nullptr)
, m_padMultiQueueVideoPreview(nullptr)
, m_pRtmp(nullptr)
{
}

nemoGstBasePlayer::~nemoGstBasePlayer()
{
	if (!m_isLinkMainPreview)
	{
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoPreviewD3D);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioConvert);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioPreview);
	}
	if (!m_isLinkRtmpPush)
	{
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkQueue);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkScale);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkRate);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkConvert);
		NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSink);
	}

	m_elmtVideoPreviewD3D = nullptr;
	m_elmtAudioConvert = nullptr;
	m_elmtAudioPreview = nullptr;

	m_elmtVideoAppSinkQueue = nullptr;
	m_elmtVideoAppSinkScale = nullptr;
	m_elmtVideoAppSinkRate = nullptr;
	m_elmtVideoAppSinkConvert = nullptr;
	m_elmtVideoAppSink = nullptr;
}

int nemoGstBasePlayer::initBasePlayer(nemoGstBasePlayerCallback* cb)
{
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoPreviewD3D);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioConvert);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioPreview);

	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkQueue);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkScale);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkRate);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkConvert);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSink);

	m_padVideoTeeAppSink = nullptr;
	m_padAudioTeeAppSink = nullptr;

	m_elmtPipeline = nullptr;
	m_pRtmp = nullptr;

	m_callback = cb;

	return 0;
}

bool nemoGstBasePlayer::isLinkedMainPreview()
{
	return m_isLinkMainPreview;
}

void nemoGstBasePlayer::linkMainPreview(void* win_handle)
{
	if (!m_elmtPipeline)
		return;

	if (m_isLinkMainPreview)
		return;

	m_elmtVideoPreviewD3D = get_element_be_check_stated(m_elmtVideoPreviewD3D, "d3dvideosink", NEMOGST_ELEMENT_NAME_VIDEO_MAIN_PREVIEW);
	m_elmtAudioConvert = get_element_be_check_stated(m_elmtAudioConvert, "audioconvert", NEMOGST_ELEMENT_NAME_AUDIO_CONVERT);
	m_elmtAudioPreview = get_element_be_check_stated(m_elmtAudioPreview, "autoaudiosink", NEMOGST_ELEMENT_NAME_AUDIO_MAIN_PREVIEW);

	if (!m_elmtVideoPreviewD3D || !m_elmtAudioConvert || !m_elmtAudioPreview)
	{
		goto LINK_FAILED;
	}

	// video render windows handle
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_elmtVideoPreviewD3D), (guintptr)win_handle);

	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoPreviewD3D
		, m_elmtAudioConvert
		, m_elmtAudioPreview
		, nullptr);

	if (!gst_element_sync_state_with_parent(m_elmtVideoPreviewD3D))
	{
		goto LINK_FAILED;
	}

	if (!gst_element_sync_state_with_parent(m_elmtAudioConvert))
	{
		goto LINK_FAILED;
	}
	if (!gst_element_sync_state_with_parent(m_elmtAudioPreview))
	{
		goto LINK_FAILED;
	}

	// link audio-convert and main preview
	if (!gst_element_link(m_elmtAudioConvert, m_elmtAudioPreview))
	{
		goto LINK_FAILED;
	}

	GstPad* pad_video_preview = gst_element_get_static_pad(m_elmtVideoPreviewD3D, "sink");
	GstPad* pad_audio_convert = gst_element_get_static_pad(m_elmtAudioConvert, "sink");

	on_link_main_preview(pad_video_preview, pad_audio_convert);

	gst_object_unref(pad_video_preview);
	gst_object_unref(pad_audio_convert);

	m_isLinkMainPreview = true;

	return;
LINK_FAILED:
	gst_bin_remove_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoPreviewD3D
		, m_elmtAudioConvert
		, m_elmtAudioPreview
		, nullptr);

	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoPreviewD3D);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioConvert);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtAudioPreview);
}

void nemoGstBasePlayer::brokenMainPreview()
{
	if (!m_elmtPipeline)
		return;

	if (!m_isLinkMainPreview)
		return;

	gst_object_ref(m_elmtVideoPreviewD3D);
	gst_bin_remove(GST_BIN(m_elmtPipeline), m_elmtVideoPreviewD3D);

	gst_object_ref(m_elmtAudioConvert);
	gst_bin_remove(GST_BIN(m_elmtPipeline), m_elmtAudioConvert);

	gst_object_ref(m_elmtAudioPreview);
	gst_bin_remove(GST_BIN(m_elmtPipeline), m_elmtAudioPreview);

	on_broken_main_preview();

// 	gst_element_set_state(m_elmtPipeline, GST_STATE_PLAYING);

	m_isLinkMainPreview = false;
}

bool nemoGstBasePlayer::isLinkRtmpPush()
{
	return m_isLinkRtmpPush;
}

void nemoGstBasePlayer::linkRtmpPush(nemoGstRtmpPush* pRtmp)
{
	if (!m_elmtPipeline)
		return;

	if (m_isLinkRtmpPush)
		return;

	ScopedLock l(m_lockRtmp);
	m_pRtmp = pRtmp;

	m_isLinkRtmpPush = true;
}

void nemoGstBasePlayer::brokenRtmpPush()
{
	if (!m_elmtPipeline)
		return;

	if (!m_isLinkRtmpPush)
		return;

	ScopedLock l(m_lockRtmp);
	m_pRtmp = nullptr;

	m_isLinkRtmpPush = false;
}

int nemoGstBasePlayer::linkConvertElementsForRtmp(int w, int h)
{
	if (!m_elmtPipeline)
		return -1;

	if (m_isLinkRtmpPush)
		return -1;

	m_elmtVideoAppSinkQueue = gst_element_factory_make("queue", NEMOGST_ELEMENT_NAME_VIDEO_APPSINK_QUEUE);
	m_elmtVideoAppSinkScale = gst_element_factory_make("videoscale", NEMOGST_ELEMENT_NAME_VIDEO_APPSINK_SCALE);
	m_elmtVideoAppSinkRate = gst_element_factory_make("videorate", NEMOGST_ELEMENT_NAME_VIDEO_APPSINK_RATE);
	m_elmtVideoAppSinkConvert = gst_element_factory_make("videoconvert", NEMOGST_ELEMENT_NAME_VIDEO_APPSINK_CONVERT);
	m_elmtVideoAppSink = gst_element_factory_make("appsink", NEMOGST_ELEMENT_NAME_VIDEO_APPSINK);

	if (!m_elmtVideoAppSinkQueue || !m_elmtVideoAppSinkScale || !m_elmtVideoAppSinkRate || !m_elmtVideoAppSinkConvert || !m_elmtVideoAppSink)
	{
		goto LINK_FAILED;
	}

	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoAppSinkQueue
		, m_elmtVideoAppSinkScale
		, m_elmtVideoAppSinkRate
		, m_elmtVideoAppSinkConvert
		, m_elmtVideoAppSink
		, nullptr);

	if (!gst_element_sync_state_with_parent(m_elmtVideoAppSinkQueue))
	{
		goto LINK_FAILED;
	}

	if (!gst_element_sync_state_with_parent(m_elmtVideoAppSinkScale))
	{
		goto LINK_FAILED;
	}

	if (!gst_element_sync_state_with_parent(m_elmtVideoAppSinkRate))
	{
		goto LINK_FAILED;
	}

	if (!gst_element_sync_state_with_parent(m_elmtVideoAppSinkConvert))
	{
		goto LINK_FAILED;
	}

	if (!gst_element_sync_state_with_parent(m_elmtVideoAppSink))
	{
		goto LINK_FAILED;
	}

	// set video sink's caps
	{
		GstCaps* caps_video_sink = gst_caps_new_simple("video/x-raw"
			, "format", G_TYPE_STRING, NEMOGST_VIDEO_RAW_FMT
			, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1
			, "framerate", GST_TYPE_FRACTION, NEMOGST_VIDEO_FRAME_RATE_NUM, NEMOGST_VIDEO_FRAME_RATE_DEN
			, "width", G_TYPE_INT, w
			, "height", G_TYPE_INT, h
			, nullptr);

		g_object_set(m_elmtVideoAppSink, "caps", caps_video_sink, nullptr);

		gst_caps_unref(caps_video_sink);
	}

	// set videoAppSink
	g_object_set(m_elmtVideoAppSink, "emit-signals", true, nullptr);
	g_signal_connect(m_elmtVideoAppSink, "new-preroll", G_CALLBACK(nemogst_signal_base_player_video_appsink_new_preroll), this);
	g_signal_connect(m_elmtVideoAppSink, "new-sample", G_CALLBACK(nemogst_signal_base_player_video_appsink_new_sample), this);

	// link video queue and scale
	if (!gst_element_link(m_elmtVideoAppSinkQueue, m_elmtVideoAppSinkScale))
	{
		goto LINK_FAILED;
	}
	// link video scale and rate
	if (!gst_element_link(m_elmtVideoAppSinkScale, m_elmtVideoAppSinkRate))
	{
		goto LINK_FAILED;
	}
	// link video rate and convert
	if (!gst_element_link(m_elmtVideoAppSinkRate, m_elmtVideoAppSinkConvert))
	{
		goto LINK_FAILED;
	}
	// link video convert and appsink
	if (!gst_element_link(m_elmtVideoAppSinkConvert, m_elmtVideoAppSink))
	{
		goto LINK_FAILED;
	}

	GstPad* pad_video_appsink_queue = gst_element_get_static_pad(m_elmtVideoAppSinkQueue, "sink");

	on_link_rtmp_push(m_pRtmp, pad_video_appsink_queue);

	gst_object_unref(pad_video_appsink_queue);

	return 0;

LINK_FAILED:
	gst_bin_remove_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoAppSinkQueue
		, m_elmtVideoAppSinkScale
		, m_elmtVideoAppSinkRate
		, m_elmtVideoAppSinkConvert
		, m_elmtVideoAppSink
		, nullptr);

	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkQueue);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkScale);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkRate);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSinkConvert);
	NEMOGST_DEFINE_RELEASE_OBJECT(m_elmtVideoAppSink);

	{
		ScopedLock l(m_lockRtmp);
		m_pRtmp = nullptr;
	}

	return -1;
}

void nemoGstBasePlayer::brokenConvertElementsForRtmp()
{
	gst_bin_remove_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoAppSinkQueue
		, m_elmtVideoAppSinkScale
		, m_elmtVideoAppSinkRate
		, m_elmtVideoAppSinkConvert
		, m_elmtVideoAppSink
		, nullptr);

	m_elmtVideoAppSinkQueue = nullptr;
	m_elmtVideoAppSinkScale = nullptr;
	m_elmtVideoAppSinkRate = nullptr;
	m_elmtVideoAppSinkConvert = nullptr;
	m_elmtVideoAppSink = nullptr;

	on_broken_rtmp_push();
}

GstElement* nemoGstBasePlayer::get_element_be_check_stated(GstElement* e, const char* fn, const char* en)
{
	if (e)
	{
		GstState s;
		GstStateChangeReturn sr = gst_element_get_state(e, &s, nullptr, 10000000);
		if (sr != GST_STATE_CHANGE_SUCCESS)
		{
			gst_object_unref(e);
			e = nullptr;
		}
	}
	if (!e)
	{
		e = gst_element_factory_make(fn, en);
	}

	return e;
}

int nemoGstBasePlayer::link_audio_convert_elemets()
{
	GstElement*	elmtAudioAppSinkQueue = nullptr;
	GstElement*	elmtAudioAppSinkResample = nullptr;
	GstElement*	elmtAudioAppSinkConvert = nullptr;

	elmtAudioAppSinkQueue = gst_element_factory_make("queue", NEMOGST_ELEMENT_NAME_AUDIO_APPSINK_QUEUE);
	elmtAudioAppSinkResample = gst_element_factory_make("audioresample", NEMOGST_ELEMENT_NAME_AUDIO_APPSINK_RESAMPLE);
	elmtAudioAppSinkConvert = gst_element_factory_make("audioconvert", NEMOGST_ELEMENT_NAME_AUDIO_APPSINK_CONVERT);
	m_elmtAudioAppSink = gst_element_factory_make("appsink", NEMOGST_ELEMENT_NAME_AUDIO_APPSINK);

	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, elmtAudioAppSinkQueue
		, elmtAudioAppSinkResample
		, elmtAudioAppSinkConvert
		, m_elmtAudioAppSink
		, nullptr);

	// set audio sink's caps
	{
		GstCaps* caps_audio_sink = gst_caps_new_simple("audio/x-raw"
			, "format", G_TYPE_STRING, NEMOGST_AUDIO_RAW_FMT_S16LE
			, "channels", G_TYPE_INT, NEMOGST_AUDIO_RAW_CH
			, "rate", G_TYPE_INT, NEMOGST_AUDIO_RAW_SAMPLE_RATE
			, "layout", G_TYPE_STRING, NEMOGST_AUDIO_RAW_LAYOUT
			, nullptr);
		g_object_set(m_elmtAudioAppSink, "caps", caps_audio_sink, nullptr);

		gst_caps_unref(caps_audio_sink);
	}

	// set audioAppSink
	g_object_set(m_elmtAudioAppSink, "emit-signals", true, nullptr);
	g_signal_connect(m_elmtAudioAppSink, "new-preroll", G_CALLBACK(nemogst_signal_base_player_audio_appsink_new_preroll), this);
	g_signal_connect(m_elmtAudioAppSink, "new-sample", G_CALLBACK(nemogst_signal_base_player_audio_appsink_new_sample), this);

	// link audio queue and audio resample
	if (!gst_element_link(elmtAudioAppSinkQueue, elmtAudioAppSinkResample))
	{
		return -1;
	}
	// link audio resample and convert
	if (!gst_element_link(elmtAudioAppSinkResample, elmtAudioAppSinkConvert))
	{
		return -1;
	}
	// link audio convert and appsink
	if (!gst_element_link(elmtAudioAppSinkConvert, m_elmtAudioAppSink))
	{
		return -1;
	}

	{
		GstPad* pad_audio_appsink_queue = gst_element_get_static_pad(elmtAudioAppSinkQueue, "sink");
		// link audio
		if (gst_pad_link(m_padAudioTeeAppSink, pad_audio_appsink_queue) != GST_PAD_LINK_OK)
		{
			return -1;
		}
		gst_object_unref(pad_audio_appsink_queue);
	}

	return 0;
}

void nemoGstBasePlayer::setBusSyncCallback(GstBus* b)
{
	// set sync-message signal
	gst_bus_enable_sync_message_emission(b);
	g_signal_connect(b, "sync-message", G_CALLBACK(nemogst_signal_base_player_bus_sync_message), this);
	g_signal_connect(b, "message::error", G_CALLBACK(nemogst_signal_base_player_bus_error), nullptr);
}

GstFlowReturn nemoGstBasePlayer::callbackVideoAppSinkNewPreroll()
{
	GstSample* gst_sample = gst_app_sink_pull_preroll((GstAppSink*)m_elmtVideoAppSink);
	if (gst_sample)
	{
		gst_sample_unref(gst_sample);
	}

	return GST_FLOW_OK;
}

GstFlowReturn nemoGstBasePlayer::callbackVideoAppSinkNewSample()
{
	GstSample* gst_sample = gst_app_sink_pull_sample((GstAppSink*)m_elmtVideoAppSink);
	if (gst_sample)
	{
		GstBuffer* gstBufer = gst_sample_get_buffer(gst_sample);
		GstSegment* segment_sample = gst_sample_get_segment(gst_sample);

		guint64 ab_t = gst_segment_to_running_time(segment_sample, GST_FORMAT_TIME, GST_BUFFER_TIMESTAMP(gstBufer)) + gst_element_get_base_time(m_elmtVideoAppSink);
		GST_BUFFER_PTS(gstBufer) = ab_t;

		ScopedLock l(m_lockRtmp);
		if (m_pRtmp) m_pRtmp->pushVideoBuffer(gst_sample);

		gst_sample_unref(gst_sample);
	}
	return GST_FLOW_OK;

}

GstFlowReturn nemoGstBasePlayer::callbackAudioAppSinkNewPreroll()
{
	GstSample* gst_sample = gst_app_sink_pull_preroll((GstAppSink*)m_elmtAudioAppSink);
	if (gst_sample)
	{
		gst_sample_unref(gst_sample);
	}
	return GST_FLOW_OK;

}

GstFlowReturn nemoGstBasePlayer::callbackAudioAppSinkNewSample()
{
	GstSample* gst_sample = gst_app_sink_pull_sample((GstAppSink*)m_elmtAudioAppSink);
	if (gst_sample)
	{
		GstBuffer* gstBufer = gst_sample_get_buffer(gst_sample);
		GstSegment* segment_sample = gst_sample_get_segment(gst_sample);

		guint64 ab_t = gst_segment_to_running_time(segment_sample, GST_FORMAT_TIME, GST_BUFFER_TIMESTAMP(gstBufer)) + gst_element_get_base_time(m_elmtVideoAppSink);
		GST_BUFFER_PTS(gstBufer) = ab_t;

		ScopedLock l(m_lockRtmp);
		if (m_pRtmp) m_pRtmp->pushAudioBuffer(gst_sample);

		gst_sample_unref(gst_sample);
	}
	return GST_FLOW_OK;

}

void nemoGstBasePlayer::callbackBusSyncMessage(GstMessage* message)
{
	switch (GST_MESSAGE_TYPE(message))
	{
	case GST_MESSAGE_ERROR:
		m_callback->postMessage(new nemoGstBasePlayerMessage(this, nemoGstBasePlayerMessage::gstMsgTypeError));
		break;
	case GST_MESSAGE_EOS:
		m_callback->postMessage(new nemoGstBasePlayerMessage(this, nemoGstBasePlayerMessage::gstMsgTypeEOS));
		break;
	case GST_MESSAGE_STATE_CHANGED:
		GstState old_state, new_state, pending_state;
		gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
		if (new_state == GST_STATE_PLAYING && message->src == GST_OBJECT_CAST(m_elmtPipeline))
		{
			m_callback->postMessage(new nemoGstBasePlayerMessage(this, nemoGstBasePlayerMessage::gstMsgTypeRunning));
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
GstFlowReturn nemogst_signal_base_player_video_appsink_new_preroll(GstElement * /*gstappsink*/, gpointer user_data)
{
	nemoGstBasePlayer* p = static_cast<nemoGstBasePlayer*>(user_data);
	if (p)
	{
 		return p->callbackVideoAppSinkNewPreroll();
	}

	return GST_FLOW_OK;
}

GstFlowReturn nemogst_signal_base_player_video_appsink_new_sample(GstElement * /*gstappsink*/, gpointer user_data)
{
	nemoGstBasePlayer* p = static_cast<nemoGstBasePlayer*>(user_data);
	if (p)
	{
		return p->callbackVideoAppSinkNewSample();
	}
	return GST_FLOW_OK;
}

GstFlowReturn nemogst_signal_base_player_audio_appsink_new_preroll(GstElement * /*gstappsink*/, gpointer user_data)
{
	nemoGstBasePlayer* p = static_cast<nemoGstBasePlayer*>(user_data);
	if (p)
	{
		return p->callbackAudioAppSinkNewPreroll();
	}
	return GST_FLOW_OK;
}

GstFlowReturn nemogst_signal_base_player_audio_appsink_new_sample(GstElement * /*gstappsink*/, gpointer user_data)
{
	nemoGstBasePlayer* p = static_cast<nemoGstBasePlayer*>(user_data);
	if (p)
	{
		return p->callbackAudioAppSinkNewSample();
	}
	return GST_FLOW_OK;
}

void nemogst_signal_base_player_bus_sync_message(GstBus* /*bus*/, GstMessage* message, gpointer user_data)
{
	nemoGstBasePlayer* p = static_cast<nemoGstBasePlayer*>(user_data);
	if (p)
	{
		p->callbackBusSyncMessage(message);
	}
}

void nemogst_signal_base_player_bus_error(GstBus* bus, GstMessage* message, gpointer user_data)
{

}