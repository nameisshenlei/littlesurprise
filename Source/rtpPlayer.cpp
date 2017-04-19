#include "rtpPlayer.h"

rtpPlayer::rtpPlayer()
	: m_elmtRtpPipeline(nullptr)
	, m_strURI(L"rtp://127.0.0.1:12345")
	, m_elmtUdpSrc(nullptr)
	, m_elmtRtpBin(nullptr)
	, m_elmtDecodeBin(nullptr)
	, m_elmtVideoConvert(nullptr)
	, m_elmtVideoD3DSink(nullptr)
	, m_elmtAudioConvert(nullptr)
	, m_elmtAudioSink(nullptr)
{

}

rtpPlayer::~rtpPlayer()
{

}

bool rtpPlayer::setRtpURI(int iUdpPort)
{
	m_strURI = L"rtp://127.0.0.1:";
	m_strURI << String(iUdpPort);

	m_elmtUdpSrc = gst_element_factory_make("udpsrc", "rtpUdpSrc");
	m_elmtRtpBin = gst_element_factory_make("rtpbin", "rtpBin");
	m_elmtDecodeBin = gst_element_factory_make("decodebin", "rtpDecodeBin");
	m_elmtVideoConvert = gst_element_factory_make("videoconvert", "rtpVideoConvert");
	m_elmtVideoD3DSink = gst_element_factory_make("d3dvideosink", "rtpD3DVideoSink");
	m_elmtAudioConvert = gst_element_factory_make("audioconvert", "rtpAudioConvert");
	m_elmtAudioSink = gst_element_factory_make("autoaudiosink", "rtpAudioSink");

	if (!m_elmtUdpSrc || !m_elmtRtpBin || !m_elmtDecodeBin || !m_elmtVideoConvert || !m_elmtVideoD3DSink || !m_elmtAudioConvert || !m_elmtAudioSink)
	{
		return false;
	}

	m_elmtRtpPipeline = gst_pipeline_new(nullptr);

	gst_bin_add_many(GST_BIN(m_elmtRtpPipeline),
		m_elmtUdpSrc,
		m_elmtRtpBin,
		m_elmtDecodeBin,
		m_elmtVideoConvert,
		m_elmtVideoD3DSink,
		m_elmtAudioConvert,
		m_elmtAudioSink);

	// udp source
	// uri
	g_object_set(m_elmtUdpSrc, "uri", m_strURI.toRawUTF8());
	// caps
	g_object_set(m_elmtUdpSrc, "caps", "application/x-rtp,media=(string)video,clock-rate=(int)90000,payload=(int)96");
	// buffer size
	g_object_set(m_elmtUdpSrc, "buffer-size", 2048000);

	// rtp bin
	{
		GstPad* udpSrcPad = nullptr;
		GstPad* rtpBinSinkPad = nullptr;
		gst_element_get_static_pad(m_elmtUdpSrc, "src");
		gst_element_get_request_pad(m_elmtRtpBin, "recv_rtp_sink_0");
		GstPadLinkReturn lret = gst_pad_link(udpSrcPad, rtpBinSinkPad);
		if (lret != GST_PAD_LINK_OK)
		{
			return false;
		}
	}

	// link others
	gboolean bret = false;
	bret = gst_element_link_many(m_elmtDecodeBin, m_elmtVideoConvert, m_elmtVideoD3DSink, nullptr);
	bret = gst_element_link_many(m_elmtDecodeBin, m_elmtAudioConvert, m_elmtAudioSink, nullptr);

	return true;
}