#ifndef NEMO_GST_HELP_FUNCTIONS_H
#define NEMO_GST_HELP_FUNCTIONS_H

#include "gstPublicHeader.h"
#include "../JuceLibraryCode/JuceHeader.h"

bool gstHelpInitEnviroment();

bool gstHelpPadIsVideo(GstPad* p);
bool gstHelpPadIsVideoAndGetSize(GstPad* p, int& w, int& h);
bool gstHelpPadIsAudio(GstPad* p);

void gstHelpSetVideoBoxParamsForWide(GstElement* video_box, int w, int h);

String gstHelpProcessToString(int c, int d);
String gstHelpSecondsToString(int t);

Drawable* qrencodeCreateFromURI(String strUri);

void gstHelpReigsterRtmp();

#endif