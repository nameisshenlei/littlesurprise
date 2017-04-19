#include "gstRtmpPushBin.h"
#include <gst/video/gstvideometa.h>

//////////////////////////////////////////////////////////////////////////
nemoGstRtmpPush::nemoGstRtmpPush()
: m_newVideoSource(false)
, m_elmtPipeline(nullptr)
, m_elmtVideoAppSrc(nullptr)
, m_elmtAudioAppSrc(nullptr)
, m_audioreadid(0)
, Thread(L"rtmpPusMsgThread")
{

}
nemoGstRtmpPush::~nemoGstRtmpPush()
{

}
int nemoGstRtmpPush::initPush(String rtmpUri, int w, int h, int br)
{
	m_elmtPipeline = nullptr;

	m_elmtAudioAppSrc = nullptr;
	m_elmtVideoAppSrc = nullptr;

	m_audioFirst = false;
	m_videoFirst = false;
	
// 	GstElement*					elmtVideoQueue = nullptr;
	GstElement*					elmtVideoEncX264 = nullptr;
	GstElement*					elmtAudioConvert = nullptr;
	GstElement*					elmtAudioEncAAC = nullptr;
	GstElement*					elmtMuxFLV = nullptr;
	GstElement*					elmtSinkRTMP = nullptr;


	// video app src
	m_elmtVideoAppSrc = gst_element_factory_make("appsrc", NEMOGST_ELEMENT_NAME_VIDEO_APPSRC);

// 	elmtVideoQueue = gst_element_factory_make("queue", NEMOGST_ELEMENT_NAME_VIDEO_QUEUE);
	// video x264 encoder
	elmtVideoEncX264 = gst_element_factory_make("x264enc", NEMOGST_ELEMENT_NAME_VIDEO_ENC_X264);

	// audio app src
	m_elmtAudioAppSrc = gst_element_factory_make("appsrc", NEMOGST_ELEMENT_NAME_AUDIO_APPSRC);
	// audio convert
	elmtAudioConvert = gst_element_factory_make("audioconvert", NEMOGST_ELEMENT_NAME_AUDIO_CONVERT);
	// audio AAC encoder
	elmtAudioEncAAC= gst_element_factory_make("voaacenc", NEMOGST_ELEMENT_NAME_AUDIO_ENC_AAC);


	// flv muxer
	elmtMuxFLV = gst_element_factory_make("flvmux", NEMOGST_ELEMENT_NAME_MUX_FLV);
	// rtmp protocol
	elmtSinkRTMP = gst_element_factory_make("rtmpsink", NEMOGST_ELEMENT_NAME_PROTOCOL_RTMP);

	if (!m_elmtVideoAppSrc || !elmtVideoEncX264 || !m_elmtAudioAppSrc || !elmtAudioConvert || !elmtAudioEncAAC || !elmtMuxFLV || !elmtSinkRTMP)
	{
		goto INIT_FAILED;
	}

	// create a new pipeline
	m_elmtPipeline = gst_pipeline_new(nullptr);
	if (!m_elmtPipeline)
	{
		goto INIT_FAILED;
	}

	// add all element in the pipeline
	gst_bin_add_many(GST_BIN(m_elmtPipeline)
		, m_elmtVideoAppSrc
// 		, elmtVideoQueue
		, elmtVideoEncX264
		, m_elmtAudioAppSrc
		, elmtAudioConvert
		, elmtAudioEncAAC
		, elmtMuxFLV
		, elmtSinkRTMP
		, nullptr);

	// set rtmp uri
	g_object_set(elmtSinkRTMP, "location", rtmpUri.toRawUTF8(), nullptr);

	// video appsrc
	{
		GstCaps* caps_video_raw = gst_caps_new_simple("video/x-raw"
			, "format", G_TYPE_STRING, NEMOGST_VIDEO_RAW_FMT
			, "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1
			, "framerate", GST_TYPE_FRACTION, NEMOGST_VIDEO_FRAME_RATE_NUM, NEMOGST_VIDEO_FRAME_RATE_DEN
			, "width", G_TYPE_INT, w
			, "height", G_TYPE_INT, h
			, nullptr);

		g_object_set(m_elmtVideoAppSrc, "caps", caps_video_raw, nullptr);
		gst_caps_unref(caps_video_raw);

		g_object_set(m_elmtVideoAppSrc, "format", GST_FORMAT_TIME, nullptr);
// 		g_object_set(m_elmtVideoAppSrc, "is-live", true, nullptr);
		g_object_set(m_elmtVideoAppSrc, "max-bytes", 0, nullptr);
	}
	// audio appsrc
	{
		GstCaps* caps_audio_raw= gst_caps_new_simple("audio/x-raw"
			, "format", G_TYPE_STRING, NEMOGST_AUDIO_RAW_FMT_S16LE
			, "layout", G_TYPE_STRING, NEMOGST_AUDIO_RAW_LAYOUT
			, "channels", G_TYPE_INT, NEMOGST_AUDIO_RAW_CH
			, "rate", G_TYPE_INT, NEMOGST_AUDIO_RAW_SAMPLE_RATE
			, nullptr);
		g_object_set(m_elmtAudioAppSrc, "caps", caps_audio_raw, nullptr);
		gst_caps_unref(caps_audio_raw);
		g_object_set(m_elmtAudioAppSrc, "format", GST_FORMAT_TIME, nullptr);
// 		g_object_set(m_elmtAudioAppSrc, "is-live", true, nullptr);
		g_object_set(m_elmtVideoAppSrc, "max-bytes", 0, nullptr);
	}


	// x264
	/*
	enum
	{
	GST_X264_ENC_PASS_CBR = 0,
	GST_X264_ENC_PASS_QUANT = 0x04,
	GST_X264_ENC_PASS_QUAL,
	GST_X264_ENC_PASS_PASS1 = 0x11,
	GST_X264_ENC_PASS_PASS2,
	GST_X264_ENC_PASS_PASS3
	};

	#define GST_X264_ENC_PASS_TYPE (gst_x264_enc_pass_get_type())
	static GType
	gst_x264_enc_pass_get_type (void)
	{
	static GType pass_type = 0;

	static const GEnumValue pass_types[] = {
	{GST_X264_ENC_PASS_CBR, "Constant Bitrate Encoding", "cbr"},
	{GST_X264_ENC_PASS_QUANT, "Constant Quantizer", "quant"},
	{GST_X264_ENC_PASS_QUAL, "Constant Quality", "qual"},
	{GST_X264_ENC_PASS_PASS1, "VBR Encoding - Pass 1", "pass1"},
	{GST_X264_ENC_PASS_PASS2, "VBR Encoding - Pass 2", "pass2"},
	{GST_X264_ENC_PASS_PASS3, "VBR Encoding - Pass 3", "pass3"},
	{0, NULL, NULL}
	};
	*/
// 	g_object_set(elmtVideoEncX264, "pass", 0x11, nullptr);

	// threads
// 	g_object_set(elmtVideoEncX264, "threads", 0, nullptr);
	// bitrate; kbit/sec.
	g_object_set(elmtVideoEncX264, "bitrate", br, nullptr);
	// tune
	/*
	{0x0, "No tuning", "none"},
	{0x1, "Still image", "stillimage"},
	{0x2, "Fast decode", "fastdecode"},
	{0x4, "Zero latency", "zerolatency"},
	{0, NULL, NULL},
	*/
	g_object_set(elmtVideoEncX264, "tune", 4, nullptr);

	// aac
	// bitrate;in bits/sec.
	g_object_set(elmtAudioEncAAC, "bitrate", 128000, nullptr);

	// flv-mux
// 	g_object_set(elmtMuxFLV, "is-live", true, nullptr);
	g_object_set(elmtMuxFLV, "streamable", true, nullptr);

	// link app-src and video encoder x264
	if (!gst_element_link(m_elmtVideoAppSrc, elmtVideoEncX264))
	{
		goto INIT_FAILED;
	}
// 	if (!gst_element_link(elmtVideoQueue, elmtVideoEncX264))
// 	{
// 		goto INIT_FAILED;
// 	}
	if (!gst_element_link(elmtVideoEncX264, elmtMuxFLV))
	{
		goto INIT_FAILED;
	}

	// link audio app src and audio encoder AAC
	if (!gst_element_link(m_elmtAudioAppSrc, elmtAudioConvert))
	{
		goto INIT_FAILED;
	}
	if (!gst_element_link(elmtAudioConvert, elmtAudioEncAAC))
	{
		goto INIT_FAILED;
	}
	// 
	if (!gst_element_link(elmtAudioEncAAC,elmtMuxFLV))
	{
		goto INIT_FAILED;
	}

	// link flv-mux and rtmp-sink
	if (!gst_element_link(elmtMuxFLV, elmtSinkRTMP))
	{
		goto INIT_FAILED;
	}

	m_timeVideoLastFrame = GST_CLOCK_TIME_NONE;
	m_timeVideoLastFrameDuration = 0;
	m_timeAudioLastFrame = GST_CLOCK_TIME_NONE;
	m_timeAudioLastFrameDuration = 0;
	m_timeAuidoDeta = 0;

	// set pipeline's bus
	GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(m_elmtPipeline));
	// set sync-message signal
// 	gst_bus_enable_sync_message_emission(bus);
// 	gst_bus_add_signal_watch_full(bus, G_PRIORITY_HIGH);
	gst_bus_set_sync_handler(bus, GstBusSyncHandler(nemogst_signal_rtmp_push_bus_watch), this,nullptr);
// 	g_signal_connect(bus, "sync-message", G_CALLBACK(nemogst_signal_rtmp_push_bus_sync_message), this);
// 	g_signal_connect(bus, "message::error", G_CALLBACK(nemogst_signal_rtmp_push_bus_error), this);
	gst_object_unref(bus);

	return 0;
INIT_FAILED:

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}
	else
	{
		gst_object_unref(m_elmtVideoAppSrc);
		gst_object_unref(elmtVideoEncX264);
		gst_object_unref(m_elmtAudioAppSrc);
		gst_object_unref(elmtAudioEncAAC);
		gst_object_unref(elmtMuxFLV);
		gst_object_unref(elmtSinkRTMP);
	}

	m_elmtAudioAppSrc = nullptr;
	m_elmtVideoAppSrc = nullptr;

	return -1;
}

int nemoGstRtmpPush::play()
{
	GstStateChangeReturn stateRet = gst_element_set_state(m_elmtPipeline, GST_STATE_PLAYING);
	if (stateRet != GST_STATE_CHANGE_SUCCESS && stateRet != GST_STATE_CHANGE_ASYNC)
	{
		return -1;
	}

	startThread();

	return 0;
}

void nemoGstRtmpPush::stop()
{
	signalThreadShouldExit();
	waitForThreadToExit(1000);

	gst_element_set_state(m_elmtPipeline, GST_STATE_NULL);

	if (m_elmtPipeline)
	{
		gst_object_unref(m_elmtPipeline);
		m_elmtPipeline = nullptr;
	}

	m_elmtAudioAppSrc = nullptr;
	m_elmtVideoAppSrc = nullptr;
}

void nemoGstRtmpPush::run()
{
	GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(m_elmtPipeline));
	GstMessage* msg = nullptr;
	GError *err = NULL;
	gchar *dbg_info = NULL;

	while (true)
	{
		msg = gst_bus_timed_pop(bus, 100 * GST_MSECOND);
		if (msg)
		{
			switch (GST_MESSAGE_TYPE(msg))
			{
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &dbg_info);
				stop();
				break;
			case GST_MESSAGE_EOS:
				// 		m_callback->postMessage(new nemoGstUriPlayerMessage(this, nemoGstUriPlayerMessage::gstMsgTypeEOS));
				break;
			case GST_MESSAGE_STATE_CHANGED:
				GstState old_state, new_state, pending_state;
				gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
				if (new_state == GST_STATE_PLAYING)
				{
					// 			m_callback->postMessage(new nemoGstUriPlayerMessage(this, nemoGstUriPlayerMessage::gstMsgTypeRunning));
				}
				break;
			}

		}
	}

	gst_object_unref(bus);
}

void nemoGstRtmpPush::setNewSrc()
{
	m_newVideoSource = true;
	m_newAudioSource = true;
}

void nemoGstRtmpPush::pushVideoBuffer(GstSample* s)
{
	GstBuffer* srcBuffer = gst_sample_get_buffer(s);

	GstBuffer* gstBuffer = gst_buffer_new();
	if (!gst_buffer_copy_into(gstBuffer, srcBuffer, GST_BUFFER_COPY_MEMORY, (gsize)0, (gsize)(-1)))
	{
		gst_buffer_unref(gstBuffer);
		return;
	}

	if (GST_STATE(m_elmtPipeline) != GST_STATE_PLAYING)
	{
		if (m_videoFirst)
		{
			gst_buffer_unref(gstBuffer);
			return;
		}
		else
		{
			// preroll video for app-src
			GST_BUFFER_PTS(gstBuffer) = 0;
			m_videoFirst = true;
		}
	}
	else
	{
		GstClockTime pipeline_base_time = gst_element_get_base_time(m_elmtPipeline);
		if (GST_BUFFER_PTS(srcBuffer) < pipeline_base_time)
		{
			// too slow
			gst_buffer_unref(gstBuffer);
			return;
		}
		else
		{
			GstClockTime new_pts = GST_BUFFER_PTS(srcBuffer) - pipeline_base_time;
			if (new_pts < m_timeVideoLastFrame)
			{
				// too slow
				gst_buffer_unref(gstBuffer);
				return;
			}
			else
			{
				GST_BUFFER_PTS(gstBuffer) = new_pts;

				if ((new_pts >(m_timeVideoLastFrame + m_timeVideoLastFrameDuration))
					&& m_newVideoSource)
				{
					// new source, so maybe have a gap
					GST_BUFFER_FLAG_SET(gstBuffer, GST_BUFFER_FLAG_DISCONT);
				}
			}
		}

		m_newVideoSource = false;
	}

	
	GST_BUFFER_DTS(gstBuffer) = GST_BUFFER_PTS(gstBuffer);
	GST_BUFFER_DURATION(gstBuffer) = GST_BUFFER_DURATION(srcBuffer);
	GST_BUFFER_OFFSET(gstBuffer) = GST_BUFFER_OFFSET_NONE;
	GST_BUFFER_OFFSET_END(gstBuffer) = GST_BUFFER_OFFSET_NONE;

	m_timeVideoLastFrame = GST_BUFFER_PTS(gstBuffer);
	m_timeVideoLastFrameDuration = GST_BUFFER_DURATION(gstBuffer);

	gst_app_src_push_buffer((GstAppSrc*)m_elmtVideoAppSrc, gstBuffer);
 
// 	gst_buffer_unref(gstBuffer);

}

void nemoGstRtmpPush::pushAudioBuffer(GstSample* s)
{
	GstBuffer* srcBuffer = gst_sample_get_buffer(s);

	GstBuffer* gstBuffer = gst_buffer_new();
	if (!gst_buffer_copy_into(gstBuffer, srcBuffer, GST_BUFFER_COPY_MEMORY, (gsize)0, (gsize)(-1)))
	{
		gst_buffer_unref(gstBuffer);
		return;
	}

	if (GST_STATE(m_elmtPipeline) != GST_STATE_PLAYING)
	{
		if (m_audioFirst)
		{
			gst_buffer_unref(gstBuffer);
			return;
		}
		else
		{
			// preroll audio for app-src
			GST_BUFFER_PTS(gstBuffer) = 0;
			m_audioFirst = true;
		}
	}
	else
	{
		GstClockTime pipeline_base_time = gst_element_get_base_time(m_elmtPipeline);
		if (GST_BUFFER_PTS(srcBuffer) < pipeline_base_time)
		{
			gst_buffer_unref(gstBuffer);
			return;
		}
		else
		{
			GstClockTime new_pts = GST_BUFFER_PTS(srcBuffer) - pipeline_base_time;
			if (new_pts < m_timeAudioLastFrame)
			{
				gst_buffer_unref(gstBuffer);
				return;
			}
			else
			{
				if (m_newAudioSource)
				{
					if ((m_timeAudioLastFrame + m_timeAudioLastFrameDuration) > new_pts)
					{
						m_timeAuidoDeta = (m_timeAudioLastFrame + m_timeAudioLastFrameDuration) - new_pts;
					}
					else
					{
						m_timeAuidoDeta = 0;
					}
				}
				GST_BUFFER_PTS(gstBuffer) = new_pts + m_timeAuidoDeta;

				if ((new_pts >(m_timeAudioLastFrame + m_timeAudioLastFrameDuration))
					&& m_newAudioSource)
				{
					// new source, so maybe have a gap
					GST_BUFFER_FLAG_SET(gstBuffer, GST_BUFFER_FLAG_DISCONT);
				}
			}
		}
		m_newAudioSource = false;
	}

// 	DBG("pts=" << GST_BUFFER_PTS(gstBuffer) << ", gap=" << GST_BUFFER_PTS(gstBuffer) - m_timeAudioLastFrame);

	GST_BUFFER_DTS(gstBuffer) = GST_BUFFER_PTS(gstBuffer);
	GST_BUFFER_DURATION(gstBuffer) = GST_BUFFER_DURATION(srcBuffer);
	GST_BUFFER_OFFSET(gstBuffer) = GST_BUFFER_OFFSET_NONE;
	GST_BUFFER_OFFSET_END(gstBuffer) = GST_BUFFER_OFFSET_NONE;

	m_timeAudioLastFrame = GST_BUFFER_PTS(gstBuffer);
	m_timeAudioLastFrameDuration = GST_BUFFER_DURATION(gstBuffer);

	gst_app_src_push_buffer((GstAppSrc*)m_elmtAudioAppSrc, gstBuffer);
// 	gst_buffer_unref(gstBuffer);
}

void nemoGstRtmpPush::callbackBusSyncMessage(GstMessage* message)
{
	GError *err = NULL;
	gchar *dbg_info = NULL;
	switch (GST_MESSAGE_TYPE(message))
	{
	case GST_MESSAGE_ERROR:
		gst_message_parse_error(message, &err, &dbg_info);
		stop();
		break;
	case GST_MESSAGE_EOS:
// 		m_callback->postMessage(new nemoGstUriPlayerMessage(this, nemoGstUriPlayerMessage::gstMsgTypeEOS));
		break;
	case GST_MESSAGE_STATE_CHANGED:
		GstState old_state, new_state, pending_state;
		gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
		if (new_state == GST_STATE_PLAYING)
		{
// 			m_callback->postMessage(new nemoGstUriPlayerMessage(this, nemoGstUriPlayerMessage::gstMsgTypeRunning));
		}
		break;
	}
}
// 
// void nemoGstRtmpPush::callbackAudioAppSrcNeedData(int needSize)
// {
// // 	if (m_audioreadid == 0)
// // 	{
// // 		m_audioreadid = g_idle_add((GSourceFunc)nemogst_signal_rtmp_push_appsrc_read_data, this);
// // 	}
// }
// 
// void nemoGstRtmpPush::callbackAudioAppSrcEnoughData()
// {
// 	if (m_audioreadid != 0)
// 	{
// 		g_source_remove(m_audioreadid);
// 		m_audioreadid = 0;
// 	}
// }
// 
// void nemoGstRtmpPush::callbackAudioReadData()
// {
// 
// }
// 
void nemogst_signal_rtmp_push_bus_sync_message(GstBus* /*bus*/, GstMessage* message, gpointer user_data)
{
	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
	if (p)
	{
		p->callbackBusSyncMessage(message);
	}
}

void nemogst_signal_rtmp_push_bus_error(GstBus* bus, GstMessage* message, gpointer user_data)
{
	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
	if (p)
	{
		p->callbackBusSyncMessage(message);
	}
}

void nemogst_signal_rtmp_push_bus_watch(GstBus* bus, GstMessage* message, gpointer user_data)
{
	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
	if (p)
	{
		p->callbackBusSyncMessage(message);
	}
}
 
// void nemogst_signal_rtmp_push_appsrc_need_data(GstElement * /*gstappsrc*/, guint arg1, gpointer user_data)
// {
// 	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
// 	if (p)
// 	{
// 		p->callbackAudioAppSrcNeedData(arg1);
// 	}
// 
// }
// 
// void nemogst_signal_rtmp_push_appsrc_enough_data(GstElement * /*gstappsrc*/, gpointer user_data)
// {
// 	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
// 	if (p)
// 	{
// 		p->callbackAudioAppSrcEnoughData();
// 	}
// 
// }
// 
// void nemogst_signal_rtmp_push_appsrc_read_data(gpointer user_data)
// {
// 	nemoGstRtmpPush* p = static_cast<nemoGstRtmpPush*>(user_data);
// 	if (p)
// 	{
// 		p->callbackAudioReadData();
// 	}
// 
// }

//////////////////////////////////////////////////////////////////////////
