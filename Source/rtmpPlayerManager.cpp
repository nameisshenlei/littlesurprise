#include "rtmpPlayerManager.h"
#include "gstUriPlayer.h"
#include "inVideoShowComponent.h"
#include "inVideoSelectedComponent.h"

rtmpPlayeresManger::rtmpPlayeresManger()
{

}

rtmpPlayeresManger::~rtmpPlayeresManger()
{
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		if (m_rtmpPlayerInfo[i].rtmpPlayer)
		{
			m_rtmpPlayerInfo[i].rtmpPlayer->stop();
			m_rtmpPlayerInfo[i].rtmpPlayer = NULL;
		}
		deleteAndZero(m_rtmpPlayerInfo[i].videoShowComponent);
		deleteAndZero(m_rtmpPlayerInfo[i].selectedComponent);
	}

	gst_object_unref(m_mainClock);
	m_mainClock = nullptr;
}

void rtmpPlayeresManger::initManager(String strIp)
{
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		m_rtmpPlayerInfo[i].strUri << strIp << String(L"mobile") << String(i);

		m_rtmpPlayerInfo[i].videoShowComponent = new inVideoShowComponent(this, m_rtmpPlayerInfo[i].strUri);
		m_rtmpPlayerInfo[i].selectedComponent = new inVideoSelectedComponent();
		m_rtmpPlayerInfo[i].rtmpPlayer = nullptr;
		m_rtmpPlayerInfo[i].timeoutCheck = Time::getCurrentTime() - RelativeTime::seconds(10);
	}

	m_mainClock = gst_system_clock_obtain();
}

void rtmpPlayeresManger::checkAndRestartRtmpPlayer(nemoGstBasePlayerCallback* cb)
{
	Time t_now = Time::getCurrentTime();
	for (int i = 0; i < NEMO_RTMP_PLAYER_SIZE; ++i)
	{
		if (!m_rtmpPlayerInfo[i].rtmpPlayer)
		{
			if (t_now > m_rtmpPlayerInfo[i].timeoutCheck)
			{
				m_rtmpPlayerInfo[i].rtmpPlayer = new nemoGstUriPlayer();
				if (m_rtmpPlayerInfo[i].rtmpPlayer->playerInit(m_mainClock, cb, m_rtmpPlayerInfo[i].strUri, m_rtmpPlayerInfo[i].videoShowComponent->getPeer()->getNativeHandle()) == 0)
				{
					m_rtmpPlayerInfo[i].rtmpPlayer->play(false);
				}
			}
		}
	}
}

void rtmpPlayeresManger::createRtmpPlayer(int i, nemoGstBasePlayerCallback* cb)
{
	if (m_rtmpPlayerInfo[i].rtmpPlayer)
	{
		m_rtmpPlayerInfo[i].rtmpPlayer->stop();
		m_rtmpPlayerInfo[i].rtmpPlayer = nullptr;
	}

	m_rtmpPlayerInfo[i].rtmpPlayer = new nemoGstUriPlayer();
	if (m_rtmpPlayerInfo[i].rtmpPlayer->playerInit(m_mainClock, cb, m_rtmpPlayerInfo[i].strUri, m_rtmpPlayerInfo[i].videoShowComponent->getPeer()->getNativeHandle()) == 0)
	{
		m_rtmpPlayerInfo[i].rtmpPlayer->play(false);
	}
}