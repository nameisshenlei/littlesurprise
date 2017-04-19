

#pragma warning(push)
#pragma warning(disable:4100)
#pragma warning(disable:4127)

#include <gst/gst.h>
#include <gst/gstplugin.h>
#include <gst/gstpluginfeature.h>
#include <gst/gstelementfactory.h>
#include <gst/video/videooverlay.h>
#include <gst/app/app.h>
#include <glib.h>

#pragma comment(lib, "glib-2.0.lib")
#pragma comment(lib, "gobject-2.0.lib")
#pragma comment(lib, "gstreamer-1.0.lib")
#pragma comment(lib, "gstapp-1.0.lib")
#pragma comment(lib, "gstvideo-1.0.lib")
#pragma comment(lib, "gstbase-1.0.lib")


#pragma warning(pop)

#include "gstHelpFunctions.h"
#include "gstElementNameString.h"

#define NEMOGST_VIDEO_RAW_FMT											"I420"
#define NEMOGST_VIDEO_FRAME_RATE_NUM									20
#define NEMOGST_VIDEO_FRAME_RATE_DEN									1

#define NEMOGST_AUDIO_RAW_FMT_F32LE										"F32LE"
#define NEMOGST_AUDIO_RAW_FMT_S16LE										"S16LE"
#define NEMOGST_AUDIO_RAW_CH											2
#define NEMOGST_AUDIO_RAW_SAMPLE_RATE									48000
#define NEMOGST_AUDIO_RAW_LAYOUT										"interleaved"
