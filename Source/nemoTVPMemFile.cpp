#include "stdafx.h"
#include "nemoTVPMemFile.h"
#include "nemoBaseHelpPublic.h"
#include "nemoWindowGlobalMutex.h"


nemoTVPMemFile::nemoTVPMemFile(String ThreadName,String fileName,int buffers,int bufferBlockSize)
: Thread(ThreadName)
, m_fileName(fileName)
, m_buffers(buffers)
, m_bufferBlockSize(bufferBlockSize)
{
}

nemoTVPMemFile::~nemoTVPMemFile()
{
	if(isThreadRunning())
	{
		signalThreadShouldExit();
		waitForThreadToExit(-1);
	}
}

void nemoTVPMemFile::run()
{
	bool fileMemCanUse = false;
	boost::interprocess::windows_shared_memory fileMem;
	boost::interprocess::mapped_region region;
	int indexBufNow = 0;

	char* pBuffer = NULL;
	int offsetBufferBlock = 0;
	int64_t lastGetDataTime = -1;

	std::vector<nemoWindowGlobalMutex*> vectorLock;


	char* pBufferNow = NULL;
	int blockBodySize = m_bufferBlockSize - 20;

	int64_t  blockTime = NULL;
	String delyText;
	String strLog;

	while(!threadShouldExit())
	{
		if(fileMemCanUse)
		{
			pBufferNow = pBuffer + indexBufNow* m_bufferBlockSize;
			if(!vectorLock[indexBufNow] || !vectorLock[indexBufNow]->lock())
			{
				Thread::sleep(1);
				continue;
			}

			blockTime = *((int64_t *)(pBufferNow+12));
			blockTime *= 1000;
			// fix; 音视频不同步，只能在这里强制提前一些。
			blockTime -= 3000000;
			// fix
			if(lastGetDataTime == -1 || blockTime > lastGetDataTime)
			{
				onReadData(pBufferNow+20,blockBodySize,blockTime);

				lastGetDataTime = blockTime;

				vectorLock[indexBufNow]->unlock();
				indexBufNow++;
				indexBufNow %= m_buffers;
			}
			else
			{
				vectorLock[indexBufNow]->unlock();
				Thread::sleep(1);
			}
		}
		else
		{
			try
			{
				for(int k = 0; k < m_buffers; ++k)
				{
					String lockName = m_fileName + String(k);

					nemoWindowGlobalMutex* pMutex = new nemoWindowGlobalMutex(lockName);
					vectorLock.push_back(pMutex);
				}

				fileMem = boost::interprocess::windows_shared_memory(boost::interprocess::open_only,m_fileName.toUTF8(),boost::interprocess::read_only);
				region = boost::interprocess::mapped_region(fileMem,boost::interprocess::read_only);
				fileMemCanUse = true;
				indexBufNow = 0;

				pBuffer = static_cast<char*>(region.get_address());
				offsetBufferBlock = 0;
				lastGetDataTime = -1;

				int memSize = region.get_size();
				if(memSize != m_buffers*(m_bufferBlockSize))
				{
					strLog = String::formatted(L"共享内存实际尺寸与指示尺寸不一致,需求[%lu],当前实际[%lu]",m_buffers*m_bufferBlockSize,memSize);
					NBLOG_WARNING_EX(L"memory",strLog.toWideCharPointer());
				}

			}
			catch (boost::interprocess::interprocess_exception& err)
			{
				strLog = L"共享内存访问失败：";
				strLog += nemoBase::helpPublic::char2wstring(err.what(),strlen(err.what())).c_str();
				strLog += L"；等待200毫秒，重新尝试";
				NBLOG_WARNING_EX(L"memory",strLog.toWideCharPointer());
			}
			Thread::sleep(200);
		}
	}

	NBLOG_INFO_EX(L"memory",L"shared memory work thread exit");

	for( size_t z=0; z < vectorLock.size(); ++z)
	{
		delete vectorLock[z];
	}
	vectorLock.resize(0);
}

int nemoTVPMemFile::openMem()
{
	setPriority(8);
	startThread();
	return 0;
}

void nemoTVPMemFile::closeMem()
{
	if(isThreadRunning())
	{
		NBLOG_INFO_EX(L"memory",L"shared memory thread close");
		signalThreadShouldExit();
		waitForThreadToExit(-1);
	}
}

nemoTVPVideoMemFile::nemoTVPVideoMemFile(String fileName,int buffers,int w,int h,AVPixelFormat fmt,bool useList)
: nemoTVPMemFile(L"tvpVideo",fileName,buffers,4*w*h+20)
, m_width(w)
, m_height(h)
, m_fmt(fmt)
, m_pCall(NULL)
, m_pBuffer(NULL)
, m_lineSize(4*w)
, m_usePacketList(useList)
{
	m_pBuffer = new char[(unsigned int)m_lineSize*h];
}

nemoTVPVideoMemFile::~nemoTVPVideoMemFile()
{
	delete[] m_pBuffer;
	m_pBuffer = NULL;
}
void nemoTVPVideoMemFile::closeMem()
{
	nemoTVPMemFile::closeMem();
	boost::mutex::scoped_lock lock(m_lockFrames);
	AVFrame* pFrame = NULL;
	while(m_listFrames.size() > 0)
	{
		pFrame = m_listFrames.front();
		m_listFrames.pop_front();
		avpicture_free((AVPicture*)pFrame);
		av_frame_free(&pFrame);
	}
}

void nemoTVPVideoMemFile::onReadData(char* buf, std::size_t s,int64_t ts)
{
	for(int i = 0; i < m_height; ++i)
	{
		memcpy(m_pBuffer + (m_height - i - 1)*m_lineSize,buf+i*m_lineSize,m_lineSize);
	}

	if(m_usePacketList)
	{
		AVFrame* pOldFrame = nullptr;
		while(isFull())
		{
			pOldFrame = removeFirst();

			if(pOldFrame)
			{
				avpicture_free((AVPicture*)pOldFrame);
				av_frame_free(&pOldFrame);
			}
			else
			{
				break;
			}
		}

		AVFrame* pFrame = av_frame_alloc();
		pFrame->width = m_width;
		pFrame->height = m_height;
		pFrame->format = m_fmt;

		if(avpicture_alloc((AVPicture*)pFrame,(AVPixelFormat)pFrame->format,pFrame->width,pFrame->height) < 0)
		{
			NBLOG_WARNING_EX(L"memory",L"alloc video frame for shared-memory,FAILED,drop first frame");
// 			pOldFrame = removeFirst();
// 			if(pOldFrame)
// 			{
// 				avpicture_free((AVPicture*)pOldFrame);
// 				av_frame_free(&pOldFrame);
// 			}
		}
		else
		{
			memcpy(pFrame->data[0],m_pBuffer,s);
			pFrame->pts = ts;

			frameIn(pFrame);
		}
	}
	else
	{
		if(m_pCall)
		{
			m_pCall->VideoDataIn(m_pBuffer,ts,s,m_width,m_height);
		}
	}
}


void nemoTVPVideoMemFile::addCallback(nemoTVPVideoMemFileCallBack* pCall)
{
	m_pCall = pCall;
}

nemoTVPAudioMemFile::nemoTVPAudioMemFile(String fileName,int buffers,int blockBodySize,int ch,int sampleRate,AVSampleFormat fmt,bool useList)
: nemoTVPMemFile(L"tvpAudio",fileName,buffers,blockBodySize+20)
, m_ch(ch)
, m_sampleRate(sampleRate)
, m_samplesPerChInBlock(0)
, m_fmt(fmt)
, m_pCall(NULL)
, m_usePacketList(useList)
{
	m_samplesPerChInBlock = blockBodySize / ch / 2;

	AVRational audioRa;
	audioRa.den = m_sampleRate;
	audioRa.num = 1;
	m_timeBlock = av_rescale_q(m_samplesPerChInBlock,audioRa,AV_TIME_BASE_Q);
	m_adjustTotalTime = 0;
	m_intputBegin = AV_NOPTS_VALUE;

	setAudioSampleRate(sampleRate);
}

nemoTVPAudioMemFile::~nemoTVPAudioMemFile()
{
 
}

void nemoTVPAudioMemFile::closeMem()
{
	nemoTVPMemFile::closeMem();
	boost::mutex::scoped_lock lock(m_lockFrames);
	AVFrame* pFrame = NULL;
	while(m_listFrames.size() > 0)
	{
		pFrame = m_listFrames.front();
		m_listFrames.pop_front();
		av_freep(&pFrame->data[0]);
		memset(pFrame->data,0,sizeof(pFrame->data));
		memset(pFrame->linesize,0,sizeof(pFrame->linesize));
		av_frame_free(&pFrame);
	}
}

void nemoTVPAudioMemFile::onReadData(char* buf, std::size_t s,int64_t ts)
{
// 	static int64_t lastPts = AV_NOPTS_VALUE;
// 	if(lastPts != AV_NOPTS_VALUE)
// 	{
// 		if((lastPts + m_timeBlock) != ts)
// 		{
// 			std::wstring wstrLog = boost::str(boost::wformat(L"audio timestamp last_pts=%d; now_pts=%d,diff=%d,maybe lost data") %lastPts %ts %(ts - lastPts));
// 			NBLOG_WARNING_EX(L"memory",wstrLog);
// 		}
// 	}
// 	lastPts = ts;

	if(m_intputBegin == AV_NOPTS_VALUE)
	{
		m_intputBegin = ts;
		m_adjustTotalTime = ts;
	}
	if(std::abs((int)(m_adjustTotalTime + m_timeBlock - ts)) > 1000000)
	{
		std::wstring wstrLog = boost::str(boost::wformat(L"audio timestamp diff = %d; adjust timestamp to %d") %(m_adjustTotalTime + m_timeBlock - ts) %ts);
		NBLOG_WARNING_EX(L"memory",wstrLog);
		m_adjustTotalTime = ts;
	}

// 	static int64_t lastTs = AV_NOPTS_VALUE;
// 	if(lastTs != AV_NOPTS_VALUE)
// 	{
// 		std::wstring wstrLog = boost::str(boost::wformat(L"audio gap %d") %(ts-lastTs));
// 		NBLOG_INFO_EX(L"memory",wstrLog);
// 	}
// 	lastTs = ts;

	if(m_usePacketList)
	{
		AVFrame* pOldFrame = nullptr;
// 		while(isFull())
// 		{
// 			pOldFrame = removeFirst();
// 
// 			av_freep(&pOldFrame->data[0]);
// 			memset(pOldFrame->data,0,sizeof(pOldFrame->data));
// 			memset(pOldFrame->linesize,0,sizeof(pOldFrame->linesize));
// 			av_frame_free(&pOldFrame);
// 
// 		}

		AVFrame* pFrame = av_frame_alloc();
		pFrame->channels = m_ch;
		pFrame->channel_layout = av_get_default_channel_layout(m_ch);
		pFrame->sample_rate = m_sampleRate;
		pFrame->format = m_fmt;
		pFrame->nb_samples = m_samplesPerChInBlock;

		if(av_samples_alloc(pFrame->data,pFrame->linesize,pFrame->channels,pFrame->nb_samples,(AVSampleFormat)pFrame->format,0) < 0)
		{
			NBLOG_WARNING_EX(L"memory",L"audio frame buffer for shared-memory alloc failed,drop first frame");
// 			pOldFrame = removeFirst();
// 
// 			av_freep(&pOldFrame->data[0]);
// 			memset(pOldFrame->data,0,sizeof(pOldFrame->data));
// 			memset(pOldFrame->linesize,0,sizeof(pOldFrame->linesize));
// 			av_frame_free(&pOldFrame);
		}
		else
		{
			memcpy(pFrame->data[0],buf,s);

			pFrame->pts = m_adjustTotalTime;
			frameIn(pFrame);
		}
	}
	else
	{
		if(m_pCall) m_pCall->AudioDataIn(buf,m_adjustTotalTime,m_samplesPerChInBlock,m_ch,s);
	}

	m_adjustTotalTime += m_timeBlock;
}

void nemoTVPAudioMemFile::addCallback(nemoTVPAudioMemFileCallBack* pCall)
{
	m_pCall = pCall;
}
