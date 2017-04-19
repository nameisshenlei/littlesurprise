#include "sharedMemoryGSTBin.h"
#include <gst/app/gstappsrc.h>
#include <gst/video/videooverlay.h>

gstSharedMemoryBin::gstSharedMemoryBin()
: m_pipeline(nullptr)
, m_videoAppSrc(nullptr)
, m_videoTee(nullptr)
, m_videoSink(nullptr)
, m_videoAppSink(nullptr)
, m_teeVideoShowPad(nullptr)
, m_videoReadDataID(0)
{

}

gstSharedMemoryBin::~gstSharedMemoryBin()
{

}

bool gstSharedMemoryBin::createBin(int videoWidth, int videoHeight, void* hwnd)
{
	if (m_pipeline)
		return false;
	m_reader = new gstSharedMemoryReader();
	m_reader->openSharedMemory(L"TVPS_OUTPUT_VIDEO_REC", 5, videoWidth*videoHeight * 4);


	m_videoReadDataID = 0;

	m_videoAppSrc = gst_element_factory_make("appsrc", "videoAppSrc");
// 	m_videoTee = gst_element_factory_make("tee", "videoTee");
// 	m_videoQueue = gst_element_factory_make("queue", "videoQueue");
	m_videoSink = gst_element_factory_make("autovideosink", "videoWindowSink");
// 	m_videoFlip = gst_element_factory_make("videoflip", "videoFlip");
	m_videoConvert = gst_element_factory_make("videoconvert", "videoConvert");

	m_videoFlip = gst_element_factory_make("decklinksink", "deck");

	if (!m_videoAppSrc || !m_videoSink || !m_videoConvert)
		return false;
// 	if (!m_videoAppSrc || !m_videoTee || !m_videoSink)
// 		return false;

	// new pipeline for bin
	m_pipeline = gst_pipeline_new("shared-memory-bin");

	// configure video appsrc
	GstCaps* videoCaps = gst_caps_new_simple("video/x-raw",
		"format", G_TYPE_STRING, "BGRA",
		"framerate", GST_TYPE_FRACTION, 30, 1,
		"pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
		"width", G_TYPE_INT, videoWidth,
		"height", G_TYPE_INT, videoHeight,
		nullptr);

	g_object_set(m_videoAppSrc, "caps", videoCaps, nullptr);

	g_signal_connect(m_videoAppSrc, "need-data", G_CALLBACK(gstSharedMemoryBin::gstCallbackVideoStatFeed), this);
	g_signal_connect(m_videoAppSrc, "enough-data", G_CALLBACK(gstSharedMemoryBin::gstCallbackVideoStopFeed), this);
// 	gst_app_src_set_max_bytes((GstAppSrc *)m_videoAppSrc, 10 * videoWidth*videoHeight * 4);
	gst_caps_unref(videoCaps);

// 	g_object_set(m_videoFlip, "method", 5, nullptr);

// 	gst_bin_add_many(GST_BIN(m_pipeline), m_videoAppSrc, m_videoTee, m_videoQueue, m_videoSink, nullptr);
	gst_bin_add_many(GST_BIN(m_pipeline), m_videoAppSrc, m_videoConvert, m_videoSink, nullptr);

	if (!gst_element_link_many(m_videoAppSrc, m_videoConvert, m_videoSink, nullptr))
	{
		return false;
	}

// 	// link
// 	if (!gst_element_link_many(m_videoAppSrc, m_videoTee, nullptr))
// 	{
// 		return false;
// 	}
// 
// 	if (!gst_element_link_many(m_videoQueue, m_videoSink, nullptr))
// 	{
// 		return false;
// 	}
// 
// 	// tee
// 	GstPadTemplate* videoTeePadTemplate = nullptr;
// 	GstPad* queueVideoShowPad = nullptr;
// 
// 	videoTeePadTemplate = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(m_videoTee), "src_%u");
// 	m_teeVideoShowPad = gst_element_request_pad(m_videoTee, videoTeePadTemplate, nullptr, nullptr);
// 	queueVideoShowPad = gst_element_get_static_pad(m_videoQueue, "sink");
// 
// 	GstPadLinkReturn linkRet = gst_pad_link(m_teeVideoShowPad, queueVideoShowPad);
// 	if (linkRet != GST_PAD_LINK_OK)
// 	{
// 		return false;
// 	}
// 	
// 	gst_object_unref(queueVideoShowPad);

	// set hwnd
// 	GstVideoOverlay * overlay = GST_VIDEO_OVERLAY(m_videoSink);
// 	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_videoSink), (guintptr)hwnd);

	GstStateChangeReturn stateRet = gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
	if (stateRet != GST_STATE_CHANGE_SUCCESS && stateRet != GST_STATE_CHANGE_ASYNC)
	{
		return false;
	}

	GST_DEBUG_BIN_TO_DOT_FILE((GstBin *)m_pipeline, GST_DEBUG_GRAPH_SHOW_ALL, "shared-memory-bin");

	m_mainLoop = g_main_loop_new(nullptr, false);
	g_main_loop_run(m_mainLoop);

// 	startTimer(10);

	return true;
}

void gstSharedMemoryBin::freeBin()
{
	if (m_reader)
	{
		m_reader->closeSharedMemory();
		deleteAndZero(m_reader);
	}
	if (m_pipeline)
	{
		gst_element_set_state(m_pipeline, GST_STATE_NULL);
		gst_object_unref(m_pipeline);
		m_pipeline = nullptr;
	}

	if (m_teeVideoShowPad)
	{
		gst_element_release_request_pad(m_videoTee, m_teeVideoShowPad);
		gst_object_unref(m_teeVideoShowPad);
		m_teeVideoShowPad = nullptr;
	}

	m_videoAppSrc = nullptr;
	m_videoTee = nullptr;
	m_videoSink = nullptr;
	m_videoQueue = nullptr;

	m_videoReadDataID = 0;
}

void gstSharedMemoryBin::gstCallbackVideoStatFeed(GstElement *source, guint size, gstSharedMemoryBin *pBin)
{
	if (pBin->m_videoReadDataID == 0)
	{
		pBin->m_videoReadDataID = g_idle_add((GSourceFunc)gstSharedMemoryBin::gstVideoReadData, pBin);
	}
}

void gstSharedMemoryBin::gstCallbackVideoStopFeed(GstElement *source, gstSharedMemoryBin *pBin)
{
	if (pBin->m_videoReadDataID != 0)
	{
		g_source_remove(pBin->m_videoReadDataID);
	}

	pBin->m_videoReadDataID = 0;
}

bool gstSharedMemoryBin::gstVideoReadData(gstSharedMemoryBin* pBin)
{
	GstBuffer* gstBuffer = nullptr;

	while (true)
	{
		gstBuffer = pBin->m_reader->getGstBuffer();
		if (gstBuffer)
			break;
		else
			Thread::sleep(10);
	}
	if (gstBuffer)
	{
		GstFlowReturn ret;
		/* Push the buffer into the appsrc */
// 		ret = gst_app_src_push_buffer((GstAppSrc*)pBin->m_videoAppSrc, gstBuffer);
		g_signal_emit_by_name(pBin->m_videoAppSrc, "push-buffer", gstBuffer, &ret);

		/* Free the buffer now that we are done with it */
		gst_buffer_unref(gstBuffer);
		if (ret != GST_FLOW_OK) 
		{
			/* We got some error, stop sending data */
			return false;
		}
	}
	return true;
}

void gstSharedMemoryBin::hiResTimerCallback()
{
	guint64 maxB = gst_app_src_get_max_bytes((GstAppSrc*)m_videoAppSrc);
	GstBuffer* gstBuffer = m_reader->getGstBuffer();
	if (gstBuffer)
	{
		GstFlowReturn ret;
		/* Push the buffer into the appsrc */
		ret = gst_app_src_push_buffer((GstAppSrc*)m_videoAppSrc, gstBuffer);

		/* Free the buffer now that we are done with it */
		gst_buffer_unref(gstBuffer);
	}
}