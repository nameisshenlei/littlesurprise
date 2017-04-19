#include "gstAppBridge.h"

void nemogst_app_bridge_linkin(nemoGstAppBridgeDst* d, nemoGstAppBridgeSrc* s)
{
	d->callbackLinkIn(d,s);

	const GenericScopedLock<SpinLock> l(s->lockBridge);
	s->appBridgeDst = d;
}

void nemogst_app_bridge_broken(nemoGstAppBridgeDst* d, nemoGstAppBridgeSrc* s)
{
	d->callbackBroken(d,s);

	const GenericScopedLock<SpinLock> l(s->lockBridge);
	s->appBridgeDst = nullptr;

}

void nemogst_app_bridge_video_sample_in(nemoGstAppBridgeDst* d, GstSample* s)
{
	GstBuffer* s_buf = gst_sample_get_buffer(s);

	g_signal_emit_by_name(d->elmtVideoSrcApp, "push-buffer", s_buf, nullptr);

	gst_sample_unref(s);
}
