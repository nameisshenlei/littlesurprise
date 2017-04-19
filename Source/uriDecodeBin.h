#ifndef NEMO_GST_URI_DECODEBIN_H
#define NEMO_GST_URI_DECODEBIN_H
#include "gstPublicHeader.h"
#include "gstHelpFunctions.h"
#include "gstUriPlaybackSignal.h"
#include "gstAppBridge.h"

#include "../JuceLibraryCode/JuceHeader.h"


struct nemoGstUriPlayback : public nemoGstAppBridgeSrc
{
	nemoGstUriPlayback::nemoGstUriPlayback(nemoGstUriPlaybackSignal* c)
	{
		signalCallback = c;
	}
	nemoGstUriPlaybackSignal*			signalCallback;
	// pipeline
	GstElement*							elmtPipeline;
	// uri decode-bin
	GstElement*							elmtUriDecodeBin;

	// video
	// video tee
	GstElement*							elmtVideoTee;
	// video queue for the render branch
	GstElement*							elmtVideoRenderQueue;
	// video convert
	GstElement*							elmtVideoRenderConvert;
	// video sink d3d for render
	GstElement*							elmtVideoRenderSinkD3D;
	// video queue for the pad-tee1
	GstElement*							elmtVideoBridgeQueue;
	// video app-sink
	GstElement*							elmtVideoBridgeSink;
	// video tee pad1 for render
	GstPad*								padVideoRenderTee;
	// video tee pad2 for other;
	GstPad*								padVideoBridgeTee;

	// audio
	// audio convert
	GstElement*							elmtAudioConvert;
	// audio sink
	GstElement*							elmtAudioSink;

private:
	nemoGstUriPlayback::nemoGstUriPlayback(){};
};

int nemogst_uri_playback_init(nemoGstUriPlayback* o, String uri, int videoWidth, int videoHeight, void* win_handle);
int nemogst_uri_playback_play(nemoGstUriPlayback* o);
void nemogst_uri_playback_stop(nemoGstUriPlayback* o);
void nemogst_uri_playback_forward(nemoGstUriPlayback* o);
void nemogst_uri_playback_back(nemoGstUriPlayback* o);
bool nemogst_uri_playback_get_process(nemoGstUriPlayback* o, gint64& d, gint64& c);
void nemogst_uri_playback_seek(nemoGstUriPlayback* o, gint64 t);

// signal callback functions for the uridecodebin in the uriplayback;
void nemogst_signal_uri_playback_uridecodebin_no_more_pads(GstElement *gstelement, gpointer user_data);
void nemogst_signal_uri_playback_uridecodebin_pad_added(GstElement *gstelement, GstPad *new_pad, gpointer user_data);
void nemogst_signal_uri_playback_uridecodebin_pad_removed(GstElement *gstelement, GstPad *old_pad, gpointer user_data);

// signal callback functions for the uri playback bus;
void nemogst_signal_uri_playback_bus_sync_message(GstBus* bus, GstMessage* message, gpointer user_data);

// signal callback functions for the video app-sink that be used for bridge
GstFlowReturn nemogst_signal_uri_playback_video_bridge(GstElement* sink, gpointer user_data);
GstFlowReturn nemogst_signal_uri_playback_video_preroll_bridge(GstElement* sink, gpointer user_data);
//////////////////////////////////////////////////////////////////////////

#endif