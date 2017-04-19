#include "gstMainPreview.h"

nemoGstMainPreview::nemoGstMainPreview()
: m_elmtVideoPreviewD3D(nullptr)
, m_elmtAudioConvert(nullptr)
, m_elmtAudioPreview(nullptr)
{

}

nemoGstMainPreview::~nemoGstMainPreview()
{

}

int nemoGstMainPreview::initAndLink(void* win_handle)
{
	m_elmtVideoPreviewD3D = gst_element_factory_make("d3dvideosink", NEMOGST_ELEMENT_NAME_VIDEO_MAIN_PREVIEW);
	m_elmtAudioConvert = gst_element_factory_make("audioconvert", NEMOGST_ELEMENT_NAME_AUDIO_CONVERT);
	m_elmtAudioPreview = gst_element_factory_make("directsoundsink", NEMOGST_ELEMENT_NAME_AUDIO_MAIN_PREVIEW);

	if (!m_elmtVideoPreviewD3D || !m_elmtAudioConvert || !m_elmtAudioPreview )
	{
		return -1;
	}

	// video render windows handle
	gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(m_elmtVideoPreviewD3D), (guintptr)win_handle);

	return 0;
}