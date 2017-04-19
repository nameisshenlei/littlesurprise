






/*
// ffmpeg to wowza with rtmp protocol
ffmpeg -re -i "D:\\movie\\BD1280.mkv" -vcodec libx264 -acodec aac -strict -2 -ab 128.k -ac 2 -ar 44100 -r 25 -s 320x240 -vb 660.k -preset slow -f flv "rtmp://127.0.0.1:1935/live/live1"
*/

// gstreamer playbin
// gst-launch-1.0.exe playbin uri="rtmp://127.0.0.1:1935/live/testRtmp"
// 
// gstreamer decodebin
// D:\studio\gst_studio\gstreamer\1.0\x86_64\bin>gst-launch-1.0.exe -vvv rtmpsrc location = "rtmp://127.0.0.1:1935/live/testRtmp" !decodebin name = f f. !videoconvert !d3dvideosink f. !audioconvert !autoaudiosink

// gst-launch-1.0.exe -vvv uridecodebin uri="file:///D:/movie/BD1280.mkv" name = f f. !videoconvert !autovideosink f. !audioconvert !autoaudiosink
//