#ifndef NEMO_RTMP_PLAYER_MANAGER_H
#define NEMO_RTMP_PLAYER_MANAGER_H

#include "../../JuceLibraryCode/JuceHeader.h"
#include "gstPublicHeader.h"

class inVideoShowComponent;
class inVideoSelectedComponent;
class nemoGstUriPlayer;
class nemoGstBasePlayerCallback;

#define NEMO_RTMP_PLAYER_SIZE			3

struct rtmpPlayerInfo
{
	inVideoShowComponent*			videoShowComponent;
	inVideoSelectedComponent*		selectedComponent;
	String							strUri;
	nemoGstUriPlayer*				rtmpPlayer;
	Time							timeoutCheck;
};

class rtmpPlayeresManger
{
public:
	rtmpPlayeresManger();
	virtual ~rtmpPlayeresManger();
protected:
	void initManager(String strIp);

	void checkAndRestartRtmpPlayer(nemoGstBasePlayerCallback* cb);

	void createRtmpPlayer(int i, nemoGstBasePlayerCallback* cb);
protected:
	rtmpPlayerInfo					m_rtmpPlayerInfo[NEMO_RTMP_PLAYER_SIZE];
	GstClock*						m_mainClock;
};

#endif