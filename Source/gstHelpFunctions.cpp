#include "gstHelpFunctions.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <windows.h>

#include "../../3rd/libqrencode/qrencode.h"
#include "./gstrtmp/gstrtmp.h"

bool gstHelpInitEnviroment()
{
#ifdef WIN32
	// set work-path for the plugins load dll file;
	wchar_t workPath[4096];
	String strPluginsPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName() + L"\\plugins";

	GetEnvironmentVariable(L"path", workPath, 4096);
	String strWorkPath = workPath;
	strWorkPath += L";";
	strWorkPath += strPluginsPath;
	SetEnvironmentVariable(L"path", strWorkPath.toWideCharPointer());

	// set environment "GST_PLUGIN_PATH";
	SetEnvironmentVariable(L"GST_PLUGIN_PATH", strPluginsPath.toWideCharPointer());
	// GST_PLUGIN_SYSTEM_PATH
	SetEnvironmentVariable(L"GST_PLUGIN_SYSTEM_PATH", strPluginsPath.toWideCharPointer());
	//GSTREAMER_1_0_ROOT_X86_64
// #ifdef _DEBUG
	String strDebugPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName() + L"\\logs";
	SetEnvironmentVariable(L"GST_DEBUG_DUMP_DOT_DIR", strDebugPath.toWideCharPointer());

	// GST_DEBUG_FILE 
	String strLogFullPath = strDebugPath + L"\\gstLogs.log";
	SetEnvironmentVariable(L"GST_DEBUG_FILE", strLogFullPath.toWideCharPointer());

	gst_debug_set_default_threshold(GST_LEVEL_WARNING);

/*#endif*/

#endif
	return true;
}

bool gstHelpPadIsVideo(GstPad* p)
{
	String str_cap_media_type;
	bool ret = false;
	int w, h;
	w = 0;
	h = 0;
	int fr_num = 0;
	int fr_den = 0;
	{
		GstCaps* c_cap = gst_pad_get_current_caps(p);
		GstStructure* struct_cap = gst_caps_get_structure(c_cap, 0);
		const gchar* name_cap = gst_structure_get_name(struct_cap);
		str_cap_media_type = name_cap;
		ret = str_cap_media_type.startsWithIgnoreCase("video");
		if (ret)
		{
			gst_structure_get_int(struct_cap, "width", &w);
			gst_structure_get_int(struct_cap, "height", &h);
			gst_structure_get_fraction(struct_cap, "framerate", &fr_num,&fr_den);
		}

		gst_object_unref(struct_cap);
		gst_caps_unref(c_cap);
	}

	return ret;
}

bool gstHelpPadIsAudio(GstPad* p)
{
	String str_cap_media_type;

	{
		GstCaps* c_cap = gst_pad_get_current_caps(p);
		GstStructure* struct_cap = gst_caps_get_structure(c_cap, 0);
		const gchar* name_cap = gst_structure_get_name(struct_cap);
		str_cap_media_type = name_cap;

		gst_object_unref(struct_cap);
		gst_caps_unref(c_cap);
	}

	return str_cap_media_type.startsWithIgnoreCase("audio");
}

bool gstHelpPadIsVideoAndGetSize(GstPad* p, int& w, int& h)
{
	String str_cap_media_type;
	bool isVideo = false;

	{
		GstCaps* c_cap = gst_pad_get_current_caps(p);
		GstStructure* struct_cap = gst_caps_get_structure(c_cap, 0);
		const gchar* name_cap = gst_structure_get_name(struct_cap);
		str_cap_media_type = name_cap;
		if (str_cap_media_type.startsWithIgnoreCase("video"))
		{
			if (gst_structure_get_int(struct_cap, "width", &w) && gst_structure_get_int(struct_cap, "height", &h))
			{
				isVideo = true;
			}
		}
		gst_object_unref(struct_cap);
		gst_caps_unref(c_cap);
	}

	return isVideo;
}

void gstHelpSetVideoBoxParamsForWide(GstElement* video_box, int w, int h)
{
	float s = (float)w / (float)h;
	float s_wide = 16.0f / 9.0f;

	if (s > s_wide)
	{
		// add borders to top and bottom;
		int b = 0 - ((int)((float)w / s_wide) - h) /2 ;

		g_object_set(video_box, "top", b, nullptr);
		g_object_set(video_box, "bottom", b, nullptr);
	}
	else if(s < s_wide)
	{
		// add border to left and right
		int b = 0 - ((int)((float)h * s_wide) - w) / 2;

		g_object_set(video_box, "top", b, nullptr);
		g_object_set(video_box, "bottom", b, nullptr);
	}
}

String gstHelpProcessToString(int c, int d)
{
	String strP;

	int h, m, s;
	h = m = s = 0;
	int h1, m1, s1;
	h1 = m1 = s1 = 0;

	// current time
	h = c / 3600;
	m = (c / 60) % 60;
	s = c % 60;

	// current time
	h1 = d / 3600;
	m1 = (d / 60) % 60;
	s1 = d % 60;

	strP = String::formatted(L"%02d:%02d:%02d / %02d:%02d:%02d", h, m, s, h1, m1, s1);

	return strP;
}

String gstHelpSecondsToString(int t)
{
	int h, m, s;
	h = m = s = 0;
	h = t / 3600;
	m = (t / 60) % 60;
	s = t % 60;

	return String::formatted(L"%02d:%02d:%02d", h, m, s);
}

#define INCHES_PER_METER (100.0/2.54)

Drawable* qrencodeCreateFromURI(String strUri)
{
	QRcode* qrcode = QRcode_encodeString8bit(strUri.toRawUTF8(), 0, QR_ECLEVEL_M);

	float f_scale = (float)(Desktop::getInstance().getDisplays().getMainDisplay().dpi * INCHES_PER_METER / 100.0);
	int symwidth, realwidth;
	unsigned char *row, *p;
	int x, y;
	int margin;

	margin = 4;
	symwidth = qrcode->width + margin * 2;
	realwidth = symwidth * 3;

	String strSvgXml;
	strSvgXml << L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
	strSvgXml << L"<!-- Created by nemo.shi with qrencode " << QRcode_APIVersionString() << L" -->\n";


	strSvgXml << String::formatted(L"<svg width=\"%0.2fcm\" height=\"%0.2fcm\" viewBox=\"0 0 %d %d\" preserveAspectRatio=\"none\" version=\"1.1\"  xmlns=\"http://www.w3.org/2000/svg\">\n",
		realwidth / f_scale, realwidth / f_scale, symwidth, symwidth);

	strSvgXml << L"\t<g id=\"QRcode\">\n";
	strSvgXml << String::formatted(L"\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#ffffff\" />\n", symwidth, symwidth);

	/* Create new viewbox for QR data */
	strSvgXml << L"\t\t<g id=\"Pattern\">\n";
	/* Write data */
	p = qrcode->data;
	for (y = 0; y < qrcode->width; y++) 
	{
		row = (p + (y*qrcode->width));

		/* no RLE */
		for (x = 0; x < qrcode->width; x++) 
		{
			if (*(row + x) & 0x1) 
			{
				strSvgXml << String::formatted(L"\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" fill=\"#000000\" />\n",
					margin + x, margin + y, 1);
			}
		}
	}

	/* Close QR data viewbox */
	strSvgXml << L"\t\t</g>\n";
	/* Close group */
	strSvgXml << L"\t</g>\n";
	/* Close SVG code */
	strSvgXml << L"</svg>\n";

	XmlElement* xmlSvg = XmlDocument::parse(strSvgXml);
	Drawable* imgQrcode = Drawable::createFromSVG(*xmlSvg);

	deleteAndZero(xmlSvg);

	return imgQrcode;
}

void gstHelpReigsterRtmp()
{
	gst_plugin_register_static(
		GST_VERSION_MAJOR,
		GST_VERSION_MINOR,
		"my-private-plugins",
		"Private elements of my application",
		GstPluginInitFunc(gst_rtmp_plugin_init),
		"1.4.5",
		"LGPL",
		"my-application-source",
		"my-application",
		"http://www.my-application.net/");

}