#include "uriDecodeBin.h"

//////////////////////////////////////////////////////////////////////////

int nemogst_uri_playback_init(nemoGstUriPlayback* o, String uri, int videoWidth, int videoHeight, void* win_handle)
{
	// uri decode bin
	o->elmtUriDecodeBin = nullptr;
	o->elmtUriDecodeBin = gst_element_factory_make("uridecodebin", "uriDecodeBin");

	if (!o->elmtUriDecodeBin)
	{
		return -1;
	}

	// set uri
	String fileUri;
	if (!uri.startsWith("file:///"))
	{
		fileUri = L"file:///";
	}
	fileUri += uri;
	g_object_set(o->elmtUriDecodeBin, "uri", fileUri.toRawUTF8(), nullptr);
	// set uridecodebin pad signal
	// no-more-pads
	g_signal_connect(o->elmtUriDecodeBin, "no-more-pads", G_CALLBACK(nemogst_signal_uri_playback_uridecodebin_no_more_pads), o);
	// added a new pad
	g_signal_connect(o->elmtUriDecodeBin, "pad-added", G_CALLBACK(nemogst_signal_uri_playback_uridecodebin_pad_added), o);
	// removed a old pad
	g_signal_connect(o->elmtUriDecodeBin, "pad-removed", G_CALLBACK(nemogst_signal_uri_playback_uridecodebin_pad_removed), o);

	// video tee
	o->elmtVideoTee = gst_element_factory_make("tee", "videoTee");

	// video queue for render
	o->elmtVideoRenderQueue = gst_element_factory_make("queue", "videoRenderQueue");

	// video convert
	o->elmtVideoRenderConvert = gst_element_factory_make("videoconvert", "videoRenderConvert");

	// video d3d sink for render
	o->elmtVideoRenderSinkD3D = gst_element_factory_make("d3dvideosink", "videoRenderSinkD3D");
	// video render windows handle
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(o->elmtVideoRenderSinkD3D), (guintptr)win_handle);

	// video queue for bridge
	o->elmtVideoBridgeQueue = gst_element_factory_make("queue", "videoBridgeQueue");

	// video app sink
	o->elmtVideoBridgeSink = gst_element_factory_make("appsink", "videoAppBridgeSink");
// 	{
// 		GstCaps* videoCaps = gst_caps_new_simple("video/x-raw",
// 			"format", G_TYPE_STRING, "BGRA",
// 			"width", G_TYPE_INT, videoWidth,
// 			"height", G_TYPE_INT, videoHeight,
// 			nullptr);
// 		g_object_set(o->elmtVideoBridgeSink, "caps", videoCaps, nullptr);
// 		gst_caps_unref(videoCaps);
// 	}

	g_object_set(o->elmtVideoBridgeSink, "emit-signals", true, nullptr);
	g_signal_connect(o->elmtVideoBridgeSink, "new-preroll", G_CALLBACK(nemogst_signal_uri_playback_video_preroll_bridge), o);
	g_signal_connect(o->elmtVideoBridgeSink, "new-sample", G_CALLBACK(nemogst_signal_uri_playback_video_bridge), o);
	
	// audio convert
	o->elmtAudioConvert = gst_element_factory_make("audioconvert", "audioConvert");
	// audio sink
	o->elmtAudioSink = gst_element_factory_make("autoaudiosink", "audioSink");

	o->elmtPipeline = nullptr;
	o->padVideoRenderTee = nullptr;
	o->padVideoBridgeTee = nullptr;
	o->appBridgeDst = nullptr;

	return 0;
}

int nemogst_uri_playback_play(nemoGstUriPlayback* o)
{
	// the pipeline is exist;
	if (o->elmtPipeline)
	{
		return -1;
	}

	// the uridecodebin is not be inited;
	if (!o->elmtUriDecodeBin)
	{
		return -1;
	}

	o->elmtPipeline = gst_pipeline_new(nullptr);

	/* for test
	gst_bin_add_many(GST_BIN(o->elmtPipeline),
		o->elmtUriDecodeBin,
		o->elmtVideoRenderConvert,
		o->elmtVideoRenderSinkD3D,
		o->elmtAudioConvert,
		o->elmtAudioSink,
		nullptr);
	// end test */

	gst_bin_add_many(GST_BIN(o->elmtPipeline),
		o->elmtUriDecodeBin,
		o->elmtVideoTee,
		o->elmtVideoRenderQueue,
		o->elmtVideoRenderConvert,
		o->elmtVideoRenderSinkD3D,
		o->elmtVideoBridgeQueue,
		o->elmtVideoBridgeSink,
		o->elmtAudioConvert,
		o->elmtAudioSink,
		nullptr);

	GstBus* bus = gst_element_get_bus(o->elmtPipeline);
	// set sync-message signal
	gst_bus_enable_sync_message_emission(bus);
	g_signal_connect(bus, "sync-message", G_CALLBACK(nemogst_signal_uri_playback_bus_sync_message), o);

	GstStateChangeReturn stateRet = gst_element_set_state(o->elmtPipeline, GST_STATE_PLAYING);
	if (stateRet != GST_STATE_CHANGE_SUCCESS && stateRet != GST_STATE_CHANGE_ASYNC)
	{
		return -1;
	}

	return 0;
}

void nemogst_uri_playback_stop(nemoGstUriPlayback* o)
{
	if (!o->elmtPipeline)
		return;

	gst_element_set_state(o->elmtPipeline, GST_STATE_NULL);

	if (o->padVideoRenderTee)
	{
		gst_element_release_request_pad(o->elmtVideoTee, o->padVideoRenderTee);
		o->padVideoRenderTee = nullptr;
	}

	if (o->padVideoBridgeTee)
	{
		gst_element_release_request_pad(o->elmtVideoTee, o->padVideoBridgeTee);
		o->padVideoBridgeTee = nullptr;
	}

	gst_object_unref(o->elmtPipeline);
	o->elmtPipeline = nullptr;
	o->elmtVideoTee = nullptr;
	o->elmtVideoRenderConvert = nullptr;
	o->elmtVideoRenderSinkD3D = nullptr;
	o->elmtVideoBridgeSink = nullptr;
	o->elmtAudioConvert = nullptr;
	o->elmtAudioSink = nullptr;
}

void nemogst_uri_playback_forward(nemoGstUriPlayback* o)
{

}

void nemogst_uri_playback_back(nemoGstUriPlayback* o)
{

}

bool nemogst_uri_playback_get_process(nemoGstUriPlayback* o, gint64& d, gint64& c)
{
	if (!gst_element_query_position(o->elmtPipeline, GST_FORMAT_TIME, &c))
		return false;

	if (!gst_element_query_duration(o->elmtPipeline, GST_FORMAT_TIME, &d))
		return false;

	return true;
}

void nemogst_uri_playback_seek(nemoGstUriPlayback* o, gint64 t)
{
	gst_element_seek_simple(o->elmtPipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, t);
}

//////////////////////////////////////////////////////////////////////////
void nemogst_signal_uri_playback_uridecodebin_no_more_pads(GstElement *gstelement, gpointer user_data)
{
}

void nemogst_signal_uri_playback_uridecodebin_pad_added(GstElement *gstelement, GstPad *new_pad, gpointer user_data)
{
	nemoGstUriPlayback* o = (nemoGstUriPlayback*)user_data;

	int w = 0;
	int h = 0;
	if (gstHelpPadIsVideoAndGetSize(new_pad,w,h))
	{
		// link uri-decodebin and video-tee
		{
			// request a source pad from video-box;
			GstPad* v_pad = gst_element_get_static_pad(o->elmtVideoTee, "sink");
			// link uri-decode-bin and video-box;
			if (gst_pad_link(new_pad, v_pad) != GST_PAD_LINK_OK)
			{
				return;
			}
			gst_object_unref(v_pad);
		}

		GstPadTemplate *tee_src_pad_template;
		// request a pad for video render from tee
		tee_src_pad_template = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(o->elmtVideoTee), "src_%u");

		// link video-tee and queue for render
		{
			o->padVideoRenderTee = gst_element_request_pad(o->elmtVideoTee, tee_src_pad_template, nullptr, nullptr);
			// get source pad from video-render-queue
			GstPad* video_pad_convert;
			video_pad_convert = gst_element_get_static_pad(o->elmtVideoRenderQueue, "sink");
			// link tee and video scale's pad
			if (gst_pad_link(o->padVideoRenderTee, video_pad_convert) != GST_PAD_LINK_OK)
			{
				return;
			}
			gst_object_unref(video_pad_convert);
		}

		// link video queue and convert
		if (!gst_element_link(o->elmtVideoRenderQueue, o->elmtVideoRenderConvert))
		{
			return;
		}

		// link video convert and video d3d render
		if (!gst_element_link(o->elmtVideoRenderConvert, o->elmtVideoRenderSinkD3D))
		{
			return;
		}
		// link video-tee and video-app for bridge
		{
			// request a pad from video-tee
			o->padVideoBridgeTee = gst_element_request_pad(o->elmtVideoTee, tee_src_pad_template, nullptr, nullptr);
			// get pad from video-bridge-queue
			GstPad* video_pad_app;
			video_pad_app = gst_element_get_static_pad(o->elmtVideoBridgeQueue, "sink");
			if (gst_pad_link(o->padVideoBridgeTee, video_pad_app) != GST_PAD_LINK_OK)
			{
				return;
			}
			gst_object_unref(video_pad_app);
		}

		// link video bridge queue and app-sink
		if (!gst_element_link(o->elmtVideoBridgeQueue, o->elmtVideoBridgeSink))
		{
			return;
		}

		// release tee pad template
		gst_object_unref(tee_src_pad_template);
	}
	else if (gstHelpPadIsAudio(new_pad))
	{
		GstPad* a_pad = gst_element_get_static_pad(o->elmtAudioConvert, "sink");
		;
		if (gst_pad_link(new_pad, a_pad) != GST_PAD_LINK_OK)
		{
			return;
		}
		gst_object_unref(a_pad);

		if (!gst_element_link(o->elmtAudioConvert, o->elmtAudioSink))
		{
			return;
		}
	}
}

void nemogst_signal_uri_playback_uridecodebin_pad_removed(GstElement *gstelement, GstPad *old_pad, gpointer user_data)
{

}

void nemogst_signal_uri_playback_bus_sync_message(GstBus* bus, GstMessage* message, gpointer user_data)
{
	nemoGstUriPlayback* o = (nemoGstUriPlayback*)user_data;
	switch (GST_MESSAGE_TYPE(message))
	{
	case GST_MESSAGE_ERROR:
		o->signalCallback->setSignal(o,nemoGstUriPlaybackSignal::signalTypeError);
		break;
	case GST_MESSAGE_EOS:
		o->signalCallback->setSignal(o,nemoGstUriPlaybackSignal::signalTypeEos);
		break;
	case GST_MESSAGE_STATE_CHANGED:
		GstState old_state, new_state, pending_state;
		gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
		if (new_state == GST_STATE_PLAYING)
		{
			o->signalCallback->setSignal(o,nemoGstUriPlaybackSignal::signalTypeRunning);
		}
		break;
	}
}

GstFlowReturn nemogst_signal_uri_playback_video_preroll_bridge(GstElement *gstappsink, gpointer user_data)
{
	nemoGstUriPlayback* o = (nemoGstUriPlayback*)user_data;

	GstSample* gst_sample = nullptr;
	g_signal_emit_by_name(o->elmtVideoBridgeSink, "pull-preroll", &gst_sample, nullptr);
	if (gst_sample)
	{
		const GenericScopedLock<SpinLock> l(o->lockBridge);
		if (o->appBridgeDst)
		{
			nemogst_app_bridge_video_sample_in(o->appBridgeDst, gst_sample);
			return GST_FLOW_OK;
		}
	}
	gst_sample_unref(gst_sample);
	return GST_FLOW_OK;
}

GstFlowReturn nemogst_signal_uri_playback_video_bridge(GstElement *gstappsink, gpointer user_data)
{
	nemoGstUriPlayback* o = (nemoGstUriPlayback*)user_data;

	GstSample* gst_sample = nullptr;
	g_signal_emit_by_name(o->elmtVideoBridgeSink, "pull-sample", &gst_sample, nullptr);
	if (gst_sample)
	{
		const GenericScopedLock<SpinLock> l(o->lockBridge);
		if (o->appBridgeDst)
		{
			nemogst_app_bridge_video_sample_in(o->appBridgeDst, gst_sample);
			return GST_FLOW_OK;
		}
	}
	gst_sample_unref(gst_sample);

	return GST_FLOW_OK;
}
