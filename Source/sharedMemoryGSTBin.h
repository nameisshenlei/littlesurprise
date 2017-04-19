#ifndef NEMO_SHARED_MEMORY_GST_BIN_H
#define NEMO_SHARED_MEMORY_GST_BIN_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "gst/gst.h"
#include "gstSharedMemoryReader.h"

class gstSharedMemoryBin : public HighResolutionTimer
{
public:
	gstSharedMemoryBin();
	virtual ~gstSharedMemoryBin();

	bool createBin(int videoWidth, int videoHeight,void* hwnd);
	void freeBin();

	static void gstCallbackVideoStatFeed(GstElement *source, guint size, gstSharedMemoryBin *pBin);
	static void gstCallbackVideoStopFeed(GstElement *source, gstSharedMemoryBin *pBin);
	static bool gstVideoReadData(gstSharedMemoryBin* pBin);

	void hiResTimerCallback();
protected:
private:
	GMainLoop*			m_mainLoop;

	GstElement*			m_pipeline;

	// video
	GstElement*			m_videoAppSrc;
	GstElement*			m_videoTee;
	GstElement*			m_videoSink;
	GstElement*			m_videoAppSink;
	GstElement*			m_videoQueue;
	GstElement*			m_videoConvert;
	GstElement*			m_videoFlip;

	GstPad*				m_teeVideoShowPad;

	guint				m_videoReadDataID;

	gstSharedMemoryReader* m_reader;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(gstSharedMemoryBin)
};

#endif