#include "gstUriPlaybackSignal.h"
//////////////////////////////////////////////////////////////////////////

nemoGstUriPlaybackSignal::nemoGstUriPlaybackSignal()
: m_p(nullptr)
{
}

nemoGstUriPlaybackSignal::~nemoGstUriPlaybackSignal()
{
}

void nemoGstUriPlaybackSignal::setSignal(nemoGstUriPlayback* p, signalType s)
{
	m_s = s;
	m_p = p;
	triggerAsyncUpdate();
}

void nemoGstUriPlaybackSignal::handleAsyncUpdate()
{
	switch (m_s)
	{
	case signalTypeError:
		onGstUriPlaybackError(m_p);
		break;
	case signalTypeEos:
		onGstUriPlaybackEos(m_p);
		break;
	case signalTypeRunning:
		onGstUriPlaybackRunning(m_p);
		break;
	}
}