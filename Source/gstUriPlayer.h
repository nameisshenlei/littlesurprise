#ifndef NEMO_GST_URI_PLAYER_H
#define NEMO_GST_URI_PLAYER_H

#include "gstBasePlayer.h"

#include "../JuceLibraryCode/JuceHeader.h"

class nemoGstRtmpPush;
class nemoGstUriPlayer;

//////////////////////////////////////////////////////////////////////////

class nemoGstUriPlayer : public Timer, public nemoGstBasePlayer
{
public:
	nemoGstUriPlayer();
	virtual ~nemoGstUriPlayer();

	int playerInit(GstClock* mainClock, nemoGstBasePlayerCallback* cb, String uri, void* win_handle);

	int play(bool needProcess);
	void stop();

	void seek(gint64 s);
	void seekForward();
	void seekBack();

	// process timer callback
	virtual void timerCallback();

	void callbackUriDecodeBinNoMorePads();
	void callbackUriDecodeBinPadAdded(GstPad* new_pad);
	void callbackUriDecodeBinPadRemoved(GstPad* old_pad);
protected:
	int init_link_video_process(
		GstElement*	elmtVideoQueue,
		GstElement* elmtVideoConvert,
		GstElement* elmtVideoRenderTee,
		GstElement* elmtMediaRenderMultiQueue,
		GstElement* elmtVideoRenderD3D);

	int init_link_audio_process(
		GstElement* elmtAudioSpaceScope);

	virtual void on_link_main_preview(GstPad* pad_video_preview, GstPad* pad_audio_convert);
	virtual void on_broken_main_preview();

	virtual void on_link_rtmp_push(nemoGstRtmpPush* pRtmp, GstPad* pad_video_appsink_queue);
	virtual void on_broken_rtmp_push();

protected:
	bool								m_haveVideo;
	bool								m_haveAudio;

	// the pad by requested from videoRenderTee will be used for local video render;
	GstPad*								m_padVideoRenderTee1;
	// the pad by requested from videoRenderTee will be used for main video preview;
	GstPad*								m_padVideoRenderTee2;
	// the pad by reuqested from audioTee will be used for audio space-scope;
	GstPad*								m_padAudioTeeSpaceScope;
	// the pad of multi-queue for video render
	GstPad*								m_padMultiQueueVideoRender;
	// the pad of multi-queue for video main preview;
	GstPad*								m_padMultiQueueVideoPreview;
	// the pad of multi-queue for audio main preview;
	GstPad*								m_padMultiQueueAudioPreview;
};

// signal callback functions for the uridecodebin in the uriplayback;
void nemogst_signal_uri_player_uridecodebin_no_more_pads(GstElement *gstelement, gpointer user_data);
void nemogst_signal_uri_player_uridecodebin_pad_added(GstElement *gstelement, GstPad *new_pad, gpointer user_data);
void nemogst_signal_uri_player_uridecodebin_pad_removed(GstElement *gstelement, GstPad *old_pad, gpointer user_data);

//////////////////////////////////////////////////////////////////////////

#endif