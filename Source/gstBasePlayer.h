#ifndef NEMO_GST_BASE_PLAYER_H
#define NEMO_GST_BASE_PLAYER_H
#include "gstPublicHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"

#define NEMOGST_DEFINE_RELEASE_OBJECT(x)				if(x) \
	{	\
		gst_object_unref(x);	\
		x = nullptr;	\
	}

class nemoGstRtmpPush;
class nemoGstBasePlayer;
//////////////////////////////////////////////////////////////////////////
class nemoGstBasePlayerMessage : public Message
{
public:
	enum gstMsgType
	{
		gstMsgTypeError,
		gstMsgTypeEOS,
		gstMsgTypeRunning,
		gstMsgTypeProcess,
	};

	nemoGstBasePlayerMessage(nemoGstBasePlayer* p, gstMsgType msgType);
	virtual ~nemoGstBasePlayerMessage();

	gstMsgType getMsgType();
	nemoGstBasePlayer* getPlayer();
protected:
	nemoGstBasePlayer*				m_player;
	gstMsgType						m_msgType;
};

//////////////////////////////////////////////////////////////////////////
class nemoGstBasePlayerProcessMessage : public nemoGstBasePlayerMessage
{
public:
	nemoGstBasePlayerProcessMessage(nemoGstBasePlayer* p, gint64 d, gint64 c);
	virtual ~nemoGstBasePlayerProcessMessage();

	gint64 getDuration();
	gint64 getCurrent();
protected:
	gint64							m_timeDuration;
	gint64							m_timeCurrent;
};

//////////////////////////////////////////////////////////////////////////
class nemoGstBasePlayerCallback : public MessageListener
{
public:
	nemoGstBasePlayerCallback();
	virtual ~nemoGstBasePlayerCallback();

	virtual void handleMessage(const Message& message);

	virtual void onBasePlayerError(nemoGstBasePlayer* p) = 0;
	virtual void onBasePlayerEOS(nemoGstBasePlayer* p) = 0;
	virtual void onBasePlayerRunning(nemoGstBasePlayer* p) = 0;
	virtual void onBasePlayerProcess(nemoGstBasePlayer* p, gint64 d, gint64 c) = 0;
};

//////////////////////////////////////////////////////////////////////////

class nemoGstBasePlayer
{
public:
	nemoGstBasePlayer();
	virtual ~nemoGstBasePlayer();

	int initBasePlayer(nemoGstBasePlayerCallback* cb);

	void linkMainPreview(void* win_handle);
	void brokenMainPreview();
	bool isLinkedMainPreview();

	void linkRtmpPush(nemoGstRtmpPush* pRtmp);
	void brokenRtmpPush();
	bool isLinkRtmpPush();

	int linkConvertElementsForRtmp(int w, int h);
	void brokenConvertElementsForRtmp();

	GstFlowReturn callbackVideoAppSinkNewPreroll();
	GstFlowReturn callbackVideoAppSinkNewSample();
	GstFlowReturn callbackAudioAppSinkNewPreroll();
	GstFlowReturn callbackAudioAppSinkNewSample();
	void callbackBusSyncMessage(GstMessage* message);
protected:
	GstElement* get_element_be_check_stated(GstElement* e, const char* fn, const char* en);
	void setBusSyncCallback(GstBus* b);
	
	int link_audio_convert_elemets();

	virtual void on_link_main_preview(GstPad* pad_video_preview, GstPad* pad_audio_convert) = 0;
	virtual void on_broken_main_preview() = 0;

	virtual void on_link_rtmp_push(nemoGstRtmpPush* pRtmp, GstPad* pad_video_appsink_queue) = 0;
	virtual void on_broken_rtmp_push() = 0;
protected:
	// callback
	nemoGstBasePlayerCallback*			m_callback;

	// pipeline
	GstElement*							m_elmtPipeline;
	// lock for rtmp-push
	CriticalSection 					m_lockRtmp;
	// nemoGstRtmpPush
	nemoGstRtmpPush*					m_pRtmp;

	bool								m_isLinkMainPreview;
	// main preview element
	GstElement*							m_elmtVideoPreviewD3D;
	GstElement*							m_elmtAudioConvert;
	GstElement*							m_elmtAudioPreview;

	bool								m_isLinkRtmpPush;
	// rtmp app sink element
	GstElement*							m_elmtVideoAppSinkQueue;
	GstElement*							m_elmtVideoAppSinkScale;
	GstElement*							m_elmtVideoAppSinkRate;
	GstElement*							m_elmtVideoAppSinkConvert;

	GstElement*							m_elmtVideoAppSink;
	GstElement*							m_elmtAudioAppSink;

	// the pad by requested from videoTee will be used for appSink;
	GstPad*								m_padVideoTeeAppSink;
	// the pad by requested from videoTee will be used for video render;
	GstPad*								m_padVideoTeeRender;
	// the pad by reuqested from audioTee will be used for appSink;
	GstPad*								m_padAudioTeeRender;
	// the pad by reuqested from audioTee will be used for audio render;
	GstPad*								m_padAudioTeeAppSink;
	// the pad of multi-queue for video main preview;
	GstPad*								m_padMultiQueueVideoPreview;
	// the pad of multi-queue for audio main preview;
	GstPad*								m_padMultiQueueAudioPreview;
};

// signal callback functions for the video appSink
GstFlowReturn nemogst_signal_base_player_video_appsink_new_preroll(GstElement *gstappsink, gpointer user_data);
GstFlowReturn nemogst_signal_base_player_video_appsink_new_sample(GstElement *gstappsink, gpointer user_data);
// signal callback functions for the audio appSink
GstFlowReturn nemogst_signal_base_player_audio_appsink_new_preroll(GstElement *gstappsink, gpointer user_data);
GstFlowReturn nemogst_signal_base_player_audio_appsink_new_sample(GstElement *gstappsink, gpointer user_data);
// signal callback functions for the Base playback bus;
void nemogst_signal_base_player_bus_sync_message(GstBus* bus, GstMessage* message, gpointer user_data);
void nemogst_signal_base_player_bus_error(GstBus* bus, GstMessage* message, gpointer user_data);

#endif