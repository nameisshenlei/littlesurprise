#ifndef NEMO_GST_MEDIA_OUTPUT_BASE_H
#define NEMO_GST_MEDIA_OUTPUT_BASE_H
#include <gst/gst.h>

class gstMediaoOutputBase
{
public:
	gstMediaoOutputBase();
	virtual ~gstMediaoOutputBase();
protected:
	bool createOutput();
	void destroyOutput();

protected:
	GstElement*						m_elmtVideoQueue;
	GstElement*						m_elmtVideoTee;
	GstElement*						m_elmtVideoConvert;
	GstElement*						m_elmtVideoRender;
	GstElement*						m_elmtVideoAppSink;
private:
};

#endif