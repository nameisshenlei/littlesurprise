#ifndef NEMO_WEB_CAM_TVP_VIDEO_MEM_FILE_H
#define NEMO_WEB_CAM_TVP_VIDEO_MEM_FILE_H

#include "nemoRawCache.h"
#include "nemoBasePacketPool.h"

class nemoTVPMemFile : public Thread
{
public:
	nemoTVPMemFile(String ThreadName,String fileName,int buffers,int bufferBlockSize);
	virtual ~nemoTVPMemFile();

	virtual int openMem();
	virtual void closeMem();
	void run();

	virtual void onReadData(char*, std::size_t s,int64_t ts) = 0;
protected:
	String m_fileName;
	int m_buffers;
	int m_bufferBlockSize;
};

class nemoTVPVideoMemFileCallBack
{
public:
	virtual void VideoDataIn(char* buf,int64_t ts,size_t s,int w, int h) = 0;
};

class nemoTVPVideoMemFile : public nemoTVPMemFile,public nemoRawCacheVideo
{
public:
	nemoTVPVideoMemFile(String fileName,int buffers,int w,int h,AVPixelFormat fmt,bool useList = false);
	virtual ~nemoTVPVideoMemFile();

	void closeMem();

	virtual void onReadData(char*, std::size_t s,int64_t ts);

	void addCallback(nemoTVPVideoMemFileCallBack* pCall);
protected:
	int m_width;
	int m_height;
	AVPixelFormat m_fmt;

	bool m_usePacketList;
	nemoTVPVideoMemFileCallBack* m_pCall;
	char* m_pBuffer;
	int m_lineSize;
};

class nemoTVPAudioMemFileCallBack
{
public:
	virtual void AudioDataIn(char* buf,int64_t ts, int nSampleNum,int ch,size_t s) = 0;
};
class nemoTVPAudioMemFile : public nemoTVPMemFile,public nemoRawCacheAudio
{
public:
	nemoTVPAudioMemFile(String fileName,int buffers,int blockBodySize,int ch,int sampleRate,AVSampleFormat fmt,bool useList = false);
	virtual ~nemoTVPAudioMemFile();

	void closeMem();
	virtual void onReadData(char*, std::size_t s,int64_t ts);

	void addCallback(nemoTVPAudioMemFileCallBack* pCall);
protected:
	int m_ch;
	int m_sampleRate;
	int m_samplesPerChInBlock;
	AVSampleFormat m_fmt;
	int64_t m_timeBlock;

	bool m_usePacketList;
	nemoTVPAudioMemFileCallBack* m_pCall;

	int64_t m_intputBegin;
	int64_t m_adjustTotalTime;
};
#endif