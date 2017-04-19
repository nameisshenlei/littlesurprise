#ifndef NEMO_GST_APP_BRIDGE_H
#define NEMO_GST_APP_BRIDGE_H
#include "gstPublicHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <list>

struct nemoGstAppBridgeSrc;
struct nemoGstAppBridgeDst;
typedef void(*callback_nemogst_bridge_link_in)(nemoGstAppBridgeDst* d,nemoGstAppBridgeSrc* s);
typedef void(*callback_nemogst_bridge_broken)(nemoGstAppBridgeDst* d,nemoGstAppBridgeSrc* s);

struct nemoGstAppBridgeDst
{
	callback_nemogst_bridge_link_in		callbackLinkIn;
	callback_nemogst_bridge_broken		callbackBroken;
	// video app-source
	GstElement*							elmtVideoSrcApp;
};

struct nemoGstAppBridgeSrc
{
	SpinLock							lockBridge;
	nemoGstAppBridgeDst*				appBridgeDst;
};

void nemogst_app_bridge_linkin(nemoGstAppBridgeDst* d, nemoGstAppBridgeSrc* s);
void nemogst_app_bridge_broken(nemoGstAppBridgeDst* d, nemoGstAppBridgeSrc* s);
void nemogst_app_bridge_video_sample_in(nemoGstAppBridgeDst* d, GstSample* s);

// bridge link-in callback

#endif