#include "gstNemoSignal.h"
//////////////////////////////////////////////////////////////////////////
// gstRtpBinSignal

void on_rtpbin_clear_pt_map(GstElement* rtpbin, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_clear_pt_map(rtpbin);
}

void on_rtpbin_bye_ssrc(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_bye_ssrc(rtpbin, session, ssrc);
}

void on_rtpbin_bye_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_bye_timeout(rtpbin, session, ssrc);
}

void on_rtpbin_new_ssrc(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_new_ssrc(rtpbin, session, ssrc);
}

void on_rtpbin_npt_stop(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_npt_stop(rtpbin, session, ssrc);
}

void on_rtpbin_sender_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_sender_timeout(rtpbin, session, ssrc);
}

void on_rtpbin_ssrc_active(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_ssrc_active(rtpbin, session, ssrc);
}

void on_rtpbin_ssrc_collision(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_ssrc_collision(rtpbin, session, ssrc);
}

void on_rtpbin_ssrc_sdes(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_ssrc_sdes(rtpbin, session, ssrc);
}

void on_rtpbin_ssrc_validated(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_ssrc_validated(rtpbin, session, ssrc);
}

void on_rtpbin_ssrc_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_ssrc_timeout(rtpbin, session, ssrc);
}

void on_rtpbin_reset_sync(GstElement* rtpbin, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_reset_sync(rtpbin);
}

void on_rtpbin_payload_type_change(GstElement *rtpbin, guint session, guint pt, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_payload_type_change(rtpbin, session, pt);
}

void on_rtpbin_new_jitterbuffer(GstElement *rtpbin, GstElement *jitterbuffer, guint session, guint ssrc, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	pRtpBin->on_class_rtpbin_new_jitterbuffer(rtpbin, jitterbuffer, session, ssrc);
}

GObject* on_rtpbin_request_internal_session(GstElement *rtpbin, guint id, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_internal_session(rtpbin, id);
}

GstCaps* on_rtpbin_request_pt_map(GstElement *rtpbin, guint session, guint pt, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_pt_map(rtpbin, session, pt);
}

GstElement* on_rtpbin_request_aux_receiver(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_aux_receiver(rtpbin, session);
}

GstElement* on_rtpbin_request_aux_sender(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_aux_sender(rtpbin, session);
}

GstElement* on_rtpbin_request_rtcp_decoder(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_rtcp_decoder(rtpbin, session);
}

GstElement* on_rtpbin_request_rtcp_encoder(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_rtcp_encoder(rtpbin, session);
}

GstElement* on_rtpbin_request_rtp_decoder(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_rtp_decoder(rtpbin, session);
}

GstElement* on_rtpbin_request_rtp_encoder(GstElement *rtpbin, guint session, gpointer user_data)
{
	gstRtpBinSignal* pRtpBin = (gstRtpBinSignal*)user_data;
	return pRtpBin->on_class_rtpbin_request_rtp_encoder(rtpbin, session);
}

gstRtpBinSignal::gstRtpBinSignal()														{}
gstRtpBinSignal::~gstRtpBinSignal()														{}

void gstRtpBinSignal::on_class_rtpbin_clear_pt_map(GstElement* /*rtpbin*/)					{}
void gstRtpBinSignal::on_class_rtpbin_bye_ssrc(
	GstElement */*rtpbin*/, guint /*session*/, guint /*ssrc*/)							{}
void gstRtpBinSignal::on_class_rtpbin_bye_timeout(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_new_ssrc(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_npt_stop(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_sender_timeout(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_ssrc_active(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_ssrc_collision(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_ssrc_sdes(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_ssrc_validated(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_ssrc_timeout(
	GstElement *rtpbin, guint session, guint ssrc)										{}
void gstRtpBinSignal::on_class_rtpbin_reset_sync(GstElement* rtpbin)							{}
void gstRtpBinSignal::on_class_rtpbin_payload_type_change(
	GstElement *rtpbin, guint session, guint pt)										{}
void gstRtpBinSignal::on_class_rtpbin_new_jitterbuffer(
	GstElement *rtpbin, GstElement *jitterbuffer, guint session, guint ssrc)			{}

GObject* gstRtpBinSignal::on_class_rtpbin_request_internal_session(
	GstElement *rtpbin, guint id)														{	return nullptr; }
GstCaps* gstRtpBinSignal::on_class_rtpbin_request_pt_map(
	GstElement *rtpbin, guint session, guint pt)										{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_aux_receiver(
	GstElement *rtpbin, guint session)													{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_aux_sender(
	GstElement *rtpbin, guint session)													{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_rtcp_decoder(
	GstElement *rtpbin, guint session)													{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_rtcp_encoder(
	GstElement *rtpbin, guint session)													{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_rtp_decoder(
	GstElement *rtpbin, guint session)													{	return nullptr; }
GstElement* gstRtpBinSignal::on_class_rtpbin_request_rtp_encoder(
	GstElement *rtpbin, guint session)													{	return nullptr; }

//////////////////////////////////////////////////////////////////////////
// gstDecodeBinSignal

void on_decodebin_drained(GstElement *bin, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	pDecodeSignal->on_class_decodebin_drained(bin);
}

void on_decodebin_unknown_type(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	pDecodeSignal->on_class_decodebin_unknown_type(bin, pad, caps);
}

gboolean on_decodebin_autoplug_continue(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	return pDecodeSignal->on_class_decodebin_autoplug_continue(bin, pad, caps);
}

GValueArray* on_decodebin_autoplug_factories(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	return pDecodeSignal->on_class_decodebin_autoplug_factories(bin, pad, caps);
}

gboolean on_decodebin_autoplug_query(GstElement *bin, GstPad *child, GstElement *pad, GstQuery *element, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	return pDecodeSignal->on_class_decodebin_autoplug_query(bin, child, pad, element);
}

GstAutoplugSelectResult on_decodebin_autoplug_select(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	return pDecodeSignal->on_class_decodebin_autoplug_select(bin, pad, caps, factory);
}

GValueArray* on_decodebin_autoplug_sort(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory, gpointer user_data)
{
	gstDecodeBinSignal* pDecodeSignal = (gstDecodeBinSignal*)(user_data);
	return pDecodeSignal->on_class_decodebin_autoplug_sort(bin, pad, caps, factory);
}

gstDecodeBinSignal::gstDecodeBinSignal()												{}
gstDecodeBinSignal::~gstDecodeBinSignal()												{}

void gstDecodeBinSignal::on_class_decodebin_drained(GstElement *bin)							{}
void gstDecodeBinSignal::on_class_decodebin_unknown_type(
	GstElement *bin, GstPad *pad, GstCaps *caps)										{}

gboolean gstDecodeBinSignal::on_class_decodebin_autoplug_continue(
	GstElement *bin, GstPad *pad, GstCaps *caps)										{	return true;	}
GValueArray* gstDecodeBinSignal::on_class_decodebin_autoplug_factories(
	GstElement *bin, GstPad *pad, GstCaps *caps)										{	return nullptr;	}
gboolean gstDecodeBinSignal::on_class_decodebin_autoplug_query(
	GstElement *bin, GstPad *child, GstElement *pad, GstQuery *element)					{	return true;	}
GstAutoplugSelectResult gstDecodeBinSignal::on_class_decodebin_autoplug_select(
	GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory)			{	return GST_AUTOPLUG_SELECT_TRY;	}
GValueArray* gstDecodeBinSignal::on_class_decodebin_autoplug_sort(
	GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory)			{	return nullptr;	}


//////////////////////////////////////////////////////////////////////////
// gstAppSrcSignal

GstFlowReturn on_appsrc_end_of_stream(GstElement *gstappsrc, gpointer user_data)
{
	gstAppSrcSignal* pAppSrc = (gstAppSrcSignal*)user_data;
	return pAppSrc->on_class_appsrc_end_of_stream(gstappsrc);
}

void on_appsrc_enough_data(GstElement *gstappsrc, gpointer user_data)
{
	gstAppSrcSignal* pAppSrc = (gstAppSrcSignal*)user_data;
	pAppSrc->on_class_appsrc_enough_data(gstappsrc);
}

void on_appsrc_need_data(GstElement *gstappsrc, guint arg1, gpointer user_data)
{
	gstAppSrcSignal* pAppSrc = (gstAppSrcSignal*)user_data;
	pAppSrc->on_class_appsrc_need_data(gstappsrc, arg1);
}

GstFlowReturn on_appsrc_push_buffer(GstElement *gstappsrc, GstBuffer *arg1, gpointer user_data)
{
	gstAppSrcSignal* pAppSrc = (gstAppSrcSignal*)user_data;
	return pAppSrc->on_class_appsrc_push_buffer(gstappsrc, arg1);
}

gboolean on_appsrc_seek_data(GstElement *gstappsrc, guint64 arg1, gpointer user_data)
{
	gstAppSrcSignal* pAppSrc = (gstAppSrcSignal*)user_data;
	return pAppSrc->on_class_appsrc_seek_data(gstappsrc, arg1);
}

gstAppSrcSignal::gstAppSrcSignal()														{}
gstAppSrcSignal::~gstAppSrcSignal()														{}

GstFlowReturn gstAppSrcSignal::on_class_appsrc_end_of_stream(GstElement *gstappsrc)			{	return GST_FLOW_EOS;	}
void gstAppSrcSignal::on_class_appsrc_enough_data(GstElement *gstappsrc)						{}
void gstAppSrcSignal::on_class_appsrc_need_data(GstElement *gstappsrc, guint arg1)			{}
GstFlowReturn gstAppSrcSignal::on_class_appsrc_push_buffer(
	GstElement *gstappsrc, GstBuffer *arg1)												{	return GST_FLOW_EOS;	}
gboolean gstAppSrcSignal::on_class_appsrc_seek_data(GstElement *gstappsrc, guint64 arg1)		{ return false; }

//////////////////////////////////////////////////////////////////////////
// gstAppSinkSignal

void on_appsink_eos(GstElement *gstappsink, gpointer user_data)
{
	gstAppSinkSignal* pAppSignal = (gstAppSinkSignal*)user_data;
	pAppSignal->on_class_appsink_eos(gstappsink);
}

GstFlowReturn on_appsink_new_preroll(GstElement *gstappsink, gpointer user_data)
{
	gstAppSinkSignal* pAppSignal = (gstAppSinkSignal*)user_data;
	return pAppSignal->on_class_appsink_new_preroll(gstappsink);
}

GstFlowReturn on_appsink_new_sample(GstElement *gstappsink, gpointer user_data)
{
	gstAppSinkSignal* pAppSignal = (gstAppSinkSignal*)user_data;
	return pAppSignal->on_class_appsink_new_sample(gstappsink);
}

GstSample* on_appsink_pull_preroll(GstElement *gstappsink, gpointer user_data)
{
	gstAppSinkSignal* pAppSignal = (gstAppSinkSignal*)user_data;
	return pAppSignal->on_class_appsink_pull_preroll(gstappsink);
}

GstSample* on_appsink_pull_sample(GstElement *gstappsink, gpointer user_data)
{
	gstAppSinkSignal* pAppSignal = (gstAppSinkSignal*)user_data;
	return pAppSignal->on_class_appsink_pull_sample(gstappsink);
}

gstAppSinkSignal::gstAppSinkSignal()													{}
gstAppSinkSignal::~gstAppSinkSignal()													{}

void gstAppSinkSignal::on_class_appsink_eos(GstElement *gstappsink)							{}
GstFlowReturn gstAppSinkSignal::on_class_appsink_new_preroll(GstElement *gstappsink)			{	return GST_FLOW_EOS; }
GstFlowReturn gstAppSinkSignal::on_class_appsink_new_sample(GstElement *gstappsink)			{	return GST_FLOW_EOS; }
GstSample* gstAppSinkSignal::on_class_appsink_pull_preroll(GstElement *gstappsink)			{	return nullptr;	}
GstSample* gstAppSinkSignal::on_class_appsink_pull_sample(GstElement *gstappsink)				{	return nullptr;	}