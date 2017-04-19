#ifndef NEMO_GST_RTP_PLAYER_H
#define NEMO_GST_RTP_PLAYER_H
#include "../JuceLibraryCode/JuceHeader.h"
#include "gstNemoSignal.h"

/*

only video

gst-launch-1.0.exe  udpsrc uri="udp://127.0.0.1:9999" caps="application/x-rtp,media=(string)video,clock-rate=(int)90000,payload=(int)96" buffer-size=10240000 \
! .recv_rtp_sink_0 rtpbin ! decodebin ! videoconvert ! autovideosink

video and audio

gst-launch-1.0.exe  udpsrc uri="udp://127.0.0.1:9999" caps="application/x-rtp,media=(string)video,clock-rate=(int)90000,payload=(int)96" buffer-size=10240000 \
! .recv_rtp_sink_0 rtpbin ! decodebin name=decoder decoder. ! videoconvert ! autovideosink decoder. ! audioconvert ! autoaudiosink

*/


class rtpPlayer : public gstRtpBinSignal
{
public:
	rtpPlayer();
	virtual ~rtpPlayer();

	bool setRtpURI(int iUdpPort);

	virtual on_rtpbin_
protected:
private:
	String								m_strURI;

	GstElement*							m_elmtRtpPipeline;

	// udp source
	GstElement*							m_elmtUdpSrc;
	// rtp bin
	GstElement*							m_elmtRtpBin;
	// decode bin
	GstElement*							m_elmtDecodeBin;
	// video
	// video convert
	GstElement*							m_elmtVideoConvert;
	// video sink 
	GstElement*							m_elmtVideoD3DSink;
	// audio
	// audio convert
	GstElement*							m_elmtAudioConvert;
	// audio sink
	GstElement*							m_elmtAudioSink;
};

#endif