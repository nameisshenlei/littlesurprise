
#include "../JuceLibraryCode/JuceHeader.h"
#include "sharedMemoryGSTBin.h"
#include <windows.h>
#include <gst/gst.h>
#include <gst/gstplugin.h>
#include <gst/gstpluginfeature.h>
#include <gst/gstelementfactory.h>
#include <glib.h>


//==============================================================================
int main(int argc, char* argv[])
{

	// ..your code goes here!
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
	SetEnvironmentVariable(L"GST_PLUGIN_SYSTEM_PATH", strPluginsPath.toWideCharPointer());
	//GSTREAMER_1_0_ROOT_X86_64
	String strDebugPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName() + L"\\debugDot";
	SetEnvironmentVariable(L"GST_DEBUG_DUMP_DOT_DIR", strDebugPath.toWideCharPointer());
#endif
	gst_init(nullptr, nullptr);
	gst_debug_set_default_threshold(GST_LEVEL_WARNING);

	gstSharedMemoryBin* m_gstSharedMemoryBin = new gstSharedMemoryBin();
	if (!m_gstSharedMemoryBin->createBin(1280, 720, nullptr))
	{
		return -1;
	}

	return 0;
}
