#ifndef NEMO_GST_RTMP_PUSH_BIN_H
#define NEMO_GST_RTMP_PUSH_BIN_H
#include "gstPublicHeader.h"
#include "gstHelpFunctions.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
/*
720P				1280x720			600~1200
360P				480x360P			300~600
270P				360x270				150~300
*/

class nemoGstRtmpPush : public Thread
{
public:
	nemoGstRtmpPush();
	virtual ~nemoGstRtmpPush();

	int initPush(String rtmpUri,int w, int h, int br);
	int play();
	void stop();

	void pushVideoBuffer(GstSample* s);
	void pushAudioBuffer(GstSample* s);

	void callbackBusSyncMessage(GstMessage* message);

	void setNewSrc();

	virtual void run();
protected:
	bool								m_newVideoSource;
	bool								m_newAudioSource;

	guint								m_audioreadid;

	String								m_rtmpUri;
	// pipeline
	GstElement*							m_elmtPipeline;
	// video app src
	GstElement*							m_elmtVideoAppSrc;
	// audio app src
	GstElement*							m_elmtAudioAppSrc;

	bool								m_videoFirst;
	GstClockTime						m_timeVideoLastFrame;
	GstClockTime						m_timeVideoLastFrameDuration;
	bool								m_audioFirst;
	GstClockTime						m_timeAudioLastFrame;
	GstClockTime						m_timeAudioLastFrameDuration;
	GstClockTime						m_timeAuidoDeta;
};

// signal callback functions for the uri playback bus;
void nemogst_signal_rtmp_push_bus_sync_message(GstBus* bus, GstMessage* message, gpointer user_data);
void nemogst_signal_rtmp_push_bus_error(GstBus* bus, GstMessage* message, gpointer user_data);
void nemogst_signal_rtmp_push_bus_watch(GstBus* bus, GstMessage* message, gpointer user_data);

// 
// void nemogst_signal_rtmp_push_appsrc_need_data(GstElement *gstappsrc, guint arg1, gpointer user_data);
// void nemogst_signal_rtmp_push_appsrc_enough_data(GstElement *gstappsrc, gpointer user_data);
// void nemogst_signal_rtmp_push_appsrc_read_data(gpointer user_data);

/*

D:\studio\gst_studio\gstreamer\1.0\x86_64\bin>gst-launch-1.0.exe -vvv  flvmux name=flv 
! rtmpsink location="rtmp://localhost:1935/live/testrtmp"
 videotestsrc! videoscale ! videoconvert ! x264enc bitrate=1000 tune="zerolatency" pass="pass1" threads=0 ! flv. 
 audiotestsrc wave=12 ! audioconvert!audioresample ! voaacenc bitrate=128000 ! flv.

*/

#endif