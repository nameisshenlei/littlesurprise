#ifndef NEMO_GST_TEST_PLAYER_H
#define NEMO_GST_TEST_PLAYER_H

#include "gstBasePlayer.h"

class nemoGstRtmpPush;

class nemoGstTestPlayer : public nemoGstBasePlayer
{
public:
	nemoGstTestPlayer();
	virtual ~nemoGstTestPlayer();

	int initPlayer(GstClock* mainClock,nemoGstBasePlayerCallback* cb);
	int play();
	void stop();

protected:
	virtual void on_link_main_preview(GstPad* pad_video_preview, GstPad* pad_audio_convert) override;
	virtual void on_broken_main_preview() override;

	virtual void on_link_rtmp_push(nemoGstRtmpPush* pRtmp, GstPad* pad_video_appsink_queue);
	virtual void on_broken_rtmp_push();
protected:
	GstElement*							m_elmtVideoFakeSink;
};

#endif