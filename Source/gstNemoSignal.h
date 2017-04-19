#ifndef NEMO_GST_SIGNAL_H
#define NEMO_GST_SIGNAL_H
#include <gst/gst.h>
//////////////////////////////////////////////////////////////////////////
// rtpbin

class gstRtpBinSignal
{
public:
	gstRtpBinSignal();
	virtual ~gstRtpBinSignal();

	virtual void on_class_rtpbin_clear_pt_map(GstElement* rtpbin);
	virtual void on_class_rtpbin_bye_ssrc(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_bye_timeout(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_new_ssrc(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_npt_stop(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_sender_timeout(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_ssrc_active(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_ssrc_collision(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_ssrc_sdes(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_ssrc_validated(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_ssrc_timeout(GstElement *rtpbin, guint session, guint ssrc);
	virtual void on_class_rtpbin_reset_sync(GstElement* rtpbin);
	virtual void on_class_rtpbin_payload_type_change(GstElement *rtpbin, guint session, guint pt);
	virtual void on_class_rtpbin_new_jitterbuffer(GstElement *rtpbin, GstElement *jitterbuffer, guint session, guint ssrc);

	virtual GObject* on_class_rtpbin_request_internal_session(GstElement *rtpbin, guint id);
	virtual GstCaps* on_class_rtpbin_request_pt_map(GstElement *rtpbin, guint session, guint pt);
	virtual GstElement* on_class_rtpbin_request_aux_receiver(GstElement *rtpbin, guint session);
	virtual GstElement* on_class_rtpbin_request_aux_sender(GstElement *rtpbin, guint session);
	virtual GstElement* on_class_rtpbin_request_rtcp_decoder(GstElement *rtpbin, guint session);
	virtual GstElement* on_class_rtpbin_request_rtcp_encoder(GstElement *rtpbin, guint session);
	virtual GstElement* on_class_rtpbin_request_rtp_decoder(GstElement *rtpbin, guint session);
	virtual GstElement* on_class_rtpbin_request_rtp_encoder(GstElement *rtpbin, guint session);
};

// signal: clear-pt-map
// Clear all previously cached pt - mapping obtained with ¡°request - pt - map¡±.
// Parameters
// rtpbin						the object which received the signal
// user_data					user data set when the signal handler was connected.
// Flags: Action
void on_rtpbin_clear_pt_map(GstElement* rtpbin, gpointer user_data);

// signal: get-internal-session
// Request the internal RTPSession object as GObject in session id .
// Parameters
// rtpbin						the object which received the signal
// id							the session id
// user_data					user data set when the signal handler was connected.
// Flags: Action
GObject* on_rtpbin_request_internal_session(GstElement *rtpbin, guint id, gpointer user_data);

// signal: on-bye-ssrc
// Notify of an SSRC that became inactive because of a BYE packet.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_bye_ssrc(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-bye-timeout
// Notify of an SSRC that has timed out because of BYE
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_bye_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-new-ssrc
// Notify of a new SSRC that entered session .
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_new_ssrc(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);


// signal: on-npt-stop
// Notify that SSRC sender has sent data up to the configured NPT stop time.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_npt_stop(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-sender-timeout
// Notify of a sender SSRC that has timed out and became a receiver
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_sender_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-ssrc-active
// Notify of a SSRC that is active, i.e., sending RTCP.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_ssrc_active(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-ssrc-collision
// Notify when we have an SSRC collision
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_ssrc_collision(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-ssrc-sdes
// Notify of a SSRC that is active, i.e., sending RTCP.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_ssrc_sdes(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-ssrc-validated
// Notify of a new SSRC that became validated.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_ssrc_validated(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: on-timeout
// Notify of an SSRC that has timed out
// Parameters
// rtpbin						the object which received the signal
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_ssrc_timeout(GstElement *rtpbin, guint session, guint ssrc, gpointer user_data);

// signal: request-pt-map
// Request the payload type as GstCaps for pt in session 
// Parameters
// rtpbin						the object which received the signal
// session						the session
// pt							the pt
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
GstCaps* on_rtpbin_request_pt_map(GstElement *rtpbin, guint session, guint pt, gpointer user_data);

// signal: reset-sync
// Reset all currently configured lip - sync parameters and require new SR packets for all streams before lip - sync is attempted again.
// Parameters
// rtpbin						the object which received the signal
// user_data					user data set when the signal handler was connected.
// Flags: Action
void on_rtpbin_reset_sync(GstElement* rtpbin, gpointer user_data);

// signal: payload-type-change
// Signal that the current payload type changed to pt in session .
// Parameters
// rtpbin						the object which received the signal
// session						the session
// pt							the pt
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_rtpbin_payload_type_change(GstElement *rtpbin, guint session, guint pt, gpointer user_data);

// signal: new-jitterbuffer
// Notify that a new jitterbuffer was created for session and ssrc.This signal can, for example, be used to configure jitterbuffer .
// Parameters
// rtpbin						the object which received the signal
// jitterbuffer					the new jitterbuffer
// session						the session
// ssrc							the SSRC
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
void on_rtpbin_new_jitterbuffer(GstElement *rtpbin, GstElement *jitterbuffer, guint session, guint ssrc, gpointer user_data);

// signal: request-aux-receiver
// Request an AUX receiver element for the given session.The AUX element will be added to the bin.
// If no handler is connected, no AUX element will be used.
// 
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_aux_receiver(GstElement *rtpbin, guint session, gpointer user_data);

// signal: request-aux-sender
// Request an AUX sender element for the given session.The AUX element will be added to the bin.
// If no handler is connected, no AUX element will be used.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_aux_sender(GstElement *rtpbin, guint session, gpointer user_data);

// signal: request-rtcp-decoder
// Request an RTCP decoder element for the given session.The decoder element will be added to the bin if not previously added.
// If no handler is connected, no encoder will be used.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_rtcp_decoder(GstElement *rtpbin, guint session, gpointer user_data);

// signal: request-rtcp-encoder
// Request an RTCP encoder element for the given session.The encoder element will be added to the bin if not previously added.
// If no handler is connected, no encoder will be used.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_rtcp_encoder(GstElement *rtpbin, guint session, gpointer user_data);

// signal: request-rtp-decoder
// Request an RTP decoder element for the given session.The decoder element will be added to the bin if not previously added.
// If no handler is connected, no encoder will be used.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_rtp_decoder(GstElement *rtpbin, guint session, gpointer user_data);

// signal: request-rtp-encoder
// Request an RTP encoder element for the given session.The encoder element will be added to the bin if not previously added.
// If no handler is connected, no encoder will be used.
// Parameters
// rtpbin						the object which received the signal
// session						the session
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
// Since 1.4
GstElement* on_rtpbin_request_rtp_encoder(GstElement *rtpbin, guint session, gpointer user_data);

//////////////////////////////////////////////////////////////////////////
// decodebin
enum GstAutoplugSelectResult
{
	GST_AUTOPLUG_SELECT_TRY,				/// Try to autoplug an element from factory
	GST_AUTOPLUG_SELECT_EXPOSE,				/// expose pad without plugging any element to it
	GST_AUTOPLUG_SELECT_SKIP,				/// skip factory and move to the next factory
};

class gstDecodeBinSignal
{
public:
	gstDecodeBinSignal();
	virtual ~gstDecodeBinSignal();

	gboolean on_class_decodebin_autoplug_continue(GstElement *bin, GstPad *pad, GstCaps *caps);
	GValueArray* on_class_decodebin_autoplug_factories(GstElement *bin, GstPad *pad, GstCaps *caps);
	gboolean on_class_decodebin_autoplug_query(GstElement *bin, GstPad *child, GstElement *pad, GstQuery *element);
	GstAutoplugSelectResult on_class_decodebin_autoplug_select(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory);
	GValueArray* on_class_decodebin_autoplug_sort(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory);
	void on_class_decodebin_drained(GstElement *bin);
	void on_class_decodebin_unknown_type(GstElement *bin, GstPad *pad, GstCaps *caps);
};

// signal: autoplug-continue
// This signal is emitted whenever decodebin finds a new stream.It is emitted before looking for any elements that can handle that stream.
// Invocation of signal handlers stops after the first signal handler returns FALSE.Signal handlers are invoked in the order they were connected in.
//
// Parameters
// bin							The decodebin.
// pad							The GstPad.
// caps							The GstCaps found.
// user_data					user data set when the signal handler was connected.
//
// Returns
// TRUE if you wish decodebin to look for elements that can handle the given caps.
// If FALSE, those caps will be considered as final and the pad will be exposed as such(see 'pad-added' signal of GstElement).
// Flags: Run Last
gboolean on_decodebin_autoplug_continue(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data);

// signal: autoplug-factories
// This function is emited when an array of possible factories for caps on pad is needed.Decodebin will by default return an array with all compatible factories, sorted by rank.
// If this function returns NULL, pad will be exposed as a final caps.
// If this function returns an empty array, the pad will be considered as having an unhandled type media type.
// Only the signal handler that is connected first will ever by invoked.Don't connect signal handlers with the G_CONNECT_AFTER flag to this signal, they will never be invoked!
// 
// Parameters
// bin							The decodebin.
// pad							The GstPad.
// caps							The GstCaps found.
// user_data					user data set when the signal handler was connected.
// 
// Returns
// a GValueArray* with a list of factories to try.The factories are by default tried in the returned order or based on the index returned by "autoplug-select".
// Flags: Run Last
GValueArray* on_decodebin_autoplug_factories(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data);

// signal:autoplug-query
// This signal is emitted whenever an autoplugged element that is not linked downstream yet and not exposed does a query.It can be used to tell the element about the downstream supported caps for example.
// 
// Parameters
// bin							The decodebin.
// child						The child element doing the query
// pad							The GstPad.
// element						The GstElement.
// query						The GstQuery.
// user_data					user data set when the signal handler was connected.
// 
// Returns
// TRUE if the query was handled, FALSE otherwise.
// Flags: Run Last
gboolean on_decodebin_autoplug_query(GstElement *bin, GstPad *child, GstElement *pad, GstQuery *element, gpointer user_data);

// signal: autoplug-select
// This signal is emitted once decodebin has found all the possible GstElementFactory that can be used to handle the given caps.For each of those factories, this signal is emitted.
// The signal handler should return a GST_TYPE_AUTOPLUG_SELECT_RESULT enum value indicating what decodebin should do next.
// The signal handler will not be invoked if any of the previously registered signal handlers(if any) return a value other than GST_AUTOPLUG_SELECT_TRY.
// Which also means that if you return GST_AUTOPLUG_SELECT_TRY from one signal handler, handlers that get registered next(again, if any) can override that decision.
//
// Parameters
// bin							The decodebin.
// pad							The GstPad.
// caps							The GstCaps.
// factory						A GstElementFactory to use.
// user_data					user data set when the signal handler was connected.
// Returns
// a GST_TYPE_AUTOPLUG_SELECT_RESULT that indicates the required operation.the default handler will always return GST_AUTOPLUG_SELECT_TRY.
// Flags: Run Last

GstAutoplugSelectResult on_decodebin_autoplug_select(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory, gpointer user_data);


// signal: autoplug-sort
// Once decodebin has found the possible GstElementFactory objects to try for caps on pad, this signal is emited.
// The purpose of the signal is for the application to perform additional sorting or filtering on the element factory array.
// The callee should copy and modify factories or return NULL if the order should not change.
// Invocation of signal handlers stops after one signal handler has returned something else than NULL.
// Signal handlers are invoked in the order they were connected in.
// Don't connect signal handlers with the G_CONNECT_AFTER flag to this signal, they will never be invoked!
//
// Parameters
// bin							The decodebin.
// pad							The GstPad.
// caps							The GstCaps.
// factory						A GstElementFactory to use.
// user_data					user data set when the signal handler was connected.
// Returns
// A new sorted array of GstElementFactory objects.
GValueArray* on_decodebin_autoplug_sort(GstElement *bin, GstPad *pad, GstCaps *caps, GstElementFactory *factory, gpointer user_data);

// signal: drained
// This signal is emitted once decodebin has finished decoding all the data.
//
// Parameters
// bin							The decodebin.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_decodebin_drained(GstElement *bin, gpointer user_data);

// signal: unknown-type
// This signal is emitted when a pad for which there is no further possible decoding is added to the decodebin.
// 
// Parameters
// bin							The decodebin.
// pad							The new pad containing caps that cannot be resolved to a 'final' stream type.
// caps							The GstCaps of the pad that cannot be resolved.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_decodebin_unknown_type(GstElement *bin, GstPad *pad, GstCaps *caps, gpointer user_data);

//////////////////////////////////////////////////////////////////////////
// appsrc

class gstAppSrcSignal
{
public:
	gstAppSrcSignal();
	virtual ~gstAppSrcSignal();

	virtual GstFlowReturn on_class_appsrc_end_of_stream(GstElement *gstappsrc);
	virtual void on_class_appsrc_enough_data(GstElement *gstappsrc);
	virtual void on_class_appsrc_need_data(GstElement *gstappsrc, guint arg1);
	virtual GstFlowReturn on_class_appsrc_push_buffer(GstElement *gstappsrc, GstBuffer *arg1);
	virtual gboolean on_class_appsrc_seek_data(GstElement *gstappsrc, guint64 arg1);
};

// signal: end-of-stream
//
// Parameters
// gstappsrc					the object which received the signal.
// user_data					user data set when the signal handler was connected.
// Returns
// Flags : Action
GstFlowReturn on_appsrc_end_of_stream(GstElement *gstappsrc, gpointer user_data);

// signal: enough-data
//
// Parameters
// gstappsrc					the object which received the signal.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_appsrc_enough_data(GstElement *gstappsrc, gpointer user_data);

// signal: need-data
//
// Parameters
// gstappsrc					the object which received the signal.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
void on_appsrc_need_data(GstElement *gstappsrc, guint arg1, gpointer user_data);

// signal: push-buffer
//
// Parameters
// gstappsrc					the object which received the signal.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
GstFlowReturn on_appsrc_push_buffer(GstElement *gstappsrc, GstBuffer *arg1, gpointer user_data);

// signal: seek-data
//
// Parameters
// gstappsrc					the object which received the signal.
// user_data					user data set when the signal handler was connected.
// Flags: Run Last
gboolean on_appsrc_seek_data(GstElement *gstappsrc, guint64 arg1, gpointer user_data);

//////////////////////////////////////////////////////////////////////////
// appsink
class gstAppSinkSignal
{
public:
	gstAppSinkSignal();
	virtual ~gstAppSinkSignal();

	virtual void on_class_appsink_eos(GstElement *gstappsink);
	virtual GstFlowReturn on_class_appsink_new_preroll(GstElement *gstappsink);
	virtual GstFlowReturn on_class_appsink_new_sample(GstElement *gstappsink);
	virtual GstSample* on_class_appsink_pull_preroll(GstElement *gstappsink);
	virtual GstSample* on_class_appsink_pull_sample(GstElement *gstappsink);
};

// signal: eos
//
// Parameters
// gstappsink					the object which received the signal.
// user_data					user data set when the signal handler was connected.
void on_appsink_eos(GstElement *gstappsink, gpointer user_data);

// signal: new-preroll
//
// Parameters
// gstappsink					the object which received the signal.
// user_data					user data set when the signal handler was connected.
GstFlowReturn on_appsink_new_preroll(GstElement *gstappsink, gpointer user_data);

// signal: new-sample
//
// Parameters
// gstappsink					the object which received the signal.
// user_data					user data set when the signal handler was connected.
GstFlowReturn on_appsink_new_sample(GstElement *gstappsink, gpointer user_data);

// signal: pull-preroll
//
// Parameters
// gstappsink					the object which received the signal.
// user_data					user data set when the signal handler was connected.
GstSample* on_appsink_pull_preroll(GstElement *gstappsink, gpointer user_data);

// signal: pull-sample
//
// Parameters
// gstappsink					the object which received the signal.
// user_data					user data set when the signal handler was connected.
GstSample* on_appsink_pull_sample(GstElement *gstappsink, gpointer user_data);
//////////////////////////////////////////////////////////////////////////
#endif