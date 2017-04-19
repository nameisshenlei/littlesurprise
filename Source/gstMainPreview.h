#ifndef NEMO_GST_MAIN_PREVIEW_H
#define NEMO_GST_MAIN_PREVIEW_H

#include "gstPublicHeader.h"

class nemoGstMainPreview
{
public:
	nemoGstMainPreview();
	virtual ~nemoGstMainPreview();

	GstElement*					m_elmtVideoPreviewD3D;
	GstElement*					m_elmtAudioConvert;
	GstElement*					m_elmtAudioPreview;

	int initAndLink(void* win_handle);
};

#endif