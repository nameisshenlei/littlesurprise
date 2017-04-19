#ifndef NEMO_GST_URI_PLAYBACK_SIGNAL_H
#define NEMO_GST_URI_PLAYBACK_SIGNAL_H

#include "gstPublicHeader.h"
#include "gstHelpFunctions.h"
struct nemoGstUriPlayback;

class nemoGstUriPlaybackSignal : public AsyncUpdater
{
public:
	nemoGstUriPlaybackSignal();
	virtual ~nemoGstUriPlaybackSignal();

	enum signalType
	{
		signalTypeError,
		signalTypeEos,
		signalTypeRunning
	};

	void setSignal(nemoGstUriPlayback* p, signalType s);

	virtual void onGstUriPlaybackError(nemoGstUriPlayback* p) = 0;
	virtual void onGstUriPlaybackEos(nemoGstUriPlayback* p) = 0;
	virtual void onGstUriPlaybackRunning(nemoGstUriPlayback* p) = 0;

	virtual void handleAsyncUpdate();
protected:
	nemoGstUriPlayback* m_p;
	signalType m_s;
};

#endif