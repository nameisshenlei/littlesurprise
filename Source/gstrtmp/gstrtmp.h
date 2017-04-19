#ifndef NEMO_GST_RTMP_H
#define NEMO_GST_RTMP_H

#include <gst/gst.h>

void gst_rtmp_log_callback(int level, const gchar * fmt, va_list vl);
void _set_debug_level(void);
gboolean gst_rtmp_plugin_init(GstPlugin * plugin);

#endif