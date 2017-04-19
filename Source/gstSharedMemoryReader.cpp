
#include "gstSharedMemoryReader.h"
#include <gst/gstpad.h>
#include <gst/gstcompat.h>

gstSharedMemoryReader::gstSharedMemoryReader()
: m_fileName(String::empty)
, m_buffers(0)
, m_bufferBlockSize(0)
, m_indexBufNow(0)
, m_lastGetDataTime(-1)
, m_beginTime(-1)
{
}

gstSharedMemoryReader::~gstSharedMemoryReader()
{
}

bool gstSharedMemoryReader::openSharedMemory(String sharedMemoryName, int buffers, int bufferBlockSize)
{
	try
	{
		m_fileName = sharedMemoryName;
		m_bufferBlockSize = bufferBlockSize;
		m_buffers = buffers;

		for (int k = 0; k < m_buffers; ++k)
		{
			String lockName = m_fileName + String(k);

			nemoWindowGlobalMutex* pMutex = new nemoWindowGlobalMutex(lockName);
			m_vectorLock.push_back(pMutex);
		}

		m_fileMem = boost::interprocess::windows_shared_memory(boost::interprocess::open_only, m_fileName.toUTF8(), boost::interprocess::read_only);
		m_region = boost::interprocess::mapped_region(m_fileMem, boost::interprocess::read_only);
		m_indexBufNow = 0;

// 		pBuffer = static_cast<char*>(region.get_address());

	}
	catch (boost::interprocess::interprocess_exception& err)
	{
		return false;
	}

	startTimer(20);

	return true;
}

void gstSharedMemoryReader::closeSharedMemory()
{
	stopTimer();

	for (size_t z = 0; z < m_vectorLock.size(); ++z)
	{
		delete m_vectorLock[z];
	}
	m_vectorLock.resize(0);

	m_fileMem = boost::interprocess::windows_shared_memory();
	m_region = boost::interprocess::mapped_region();
}
// 
void gstSharedMemoryReader::hiResTimerCallback()
{
	GstBuffer *gstBuffer = nullptr;
	char* pBuffer = static_cast<char*>(m_region.get_address());
	char* pBufferNow = nullptr;
	int64_t  blockTime = -1;

	pBufferNow = pBuffer + m_indexBufNow* (m_bufferBlockSize + 20);
	if (!m_vectorLock[m_indexBufNow] || !m_vectorLock[m_indexBufNow]->lock())
	{
		return;
	}

	blockTime = *((int64_t *)(pBufferNow + 12));
	blockTime *= 1000000;
	if (m_beginTime == -1)
	{
		m_beginTime = blockTime;
	}
	blockTime -= m_beginTime;
	if (m_lastGetDataTime == -1 || blockTime > m_lastGetDataTime)
	{
		GstBuffer *gstBuffer;
		GstFlowReturn ret;
		int i;
		gint8 *raw;

		gstBuffer = gst_buffer_new_and_alloc(m_bufferBlockSize);
		GstMapInfo map;
		if (gst_buffer_map(gstBuffer, &map, GST_MAP_READ)) 
		{
			for (int i = 0; i < 720; ++i)
			{
				memcpy(map.data + 1280 * 4 * i, pBufferNow + 1280 * 4 * (720 - 1 - i), 1280 * 4);
			}
// 			memcpy(map.data, pBufferNow, m_bufferBlockSize);
			gst_buffer_unmap(gstBuffer, &map);
		}

		GST_BUFFER_PTS(gstBuffer) = blockTime;
		GST_BUFFER_DTS(gstBuffer) = blockTime;
		GST_BUFFER_DURATION(gstBuffer) = 0;
		GST_BUFFER_OFFSET(gstBuffer) = GST_BUFFER_OFFSET_NONE;
		GST_BUFFER_OFFSET_END(gstBuffer) = GST_BUFFER_OFFSET_NONE;

		m_lastGetDataTime = blockTime;

		m_vectorLock[m_indexBufNow]->unlock();
		m_indexBufNow++;
		m_indexBufNow %= m_buffers;

		boost::mutex::scoped_lock lock(m_lockGstBuffer);
		m_listGstBuffer.push_back(gstBuffer);
	}
	else
	{
		m_vectorLock[m_indexBufNow]->unlock();
	}
}

GstBuffer* gstSharedMemoryReader::getGstBuffer()
{
	GstBuffer* gstBuffer = nullptr;
	boost::mutex::scoped_lock lock(m_lockGstBuffer);
	if (m_listGstBuffer.size() > 0)
	{
		gstBuffer = m_listGstBuffer.front();
		m_listGstBuffer.pop_front();
	}

	return gstBuffer;
}

// GstBuffer* gstSharedMemoryReader::getGstBuffer()
// {
// 	GstBuffer *gstBuffer = nullptr;
// 
// 	char* pBuffer = static_cast<char*>(m_region.get_address());
// 	char* pBufferNow = nullptr;
// 	int64_t  blockTime = NULL;
// 
// 	pBufferNow = pBuffer + m_indexBufNow* (m_bufferBlockSize+20);
// 	if (!m_vectorLock[m_indexBufNow] || !m_vectorLock[m_indexBufNow]->must_lock())
// 	{
// 		return gstBuffer;
// 	}
// 
// 	blockTime = *((int64_t *)(pBufferNow + 12));
// 	blockTime *= 1000000;
// 	if (m_beginTime == -1)
// 	{
// 		m_beginTime = blockTime;
// 	}
// 	blockTime -= m_beginTime;
// 
// 	if (m_lastGetDataTime == -1 || blockTime > m_lastGetDataTime)
// 	{
// 		GstFlowReturn ret;
// 		int i;
// 		gint8 *raw;
// 
// 		gstBuffer = gst_buffer_new_and_alloc(m_bufferBlockSize);
// 		GstMapInfo map;
// 		if (gst_buffer_map(gstBuffer, &map, GST_MAP_WRITE))
// 		{
// 			memcpy(map.data, pBufferNow, m_bufferBlockSize);
// // 			memset(map.data, m_bufferBlockSize, 111);
// 			gst_buffer_unmap(gstBuffer, &map);
// 		}
// 		else
// 		{
// 			return nullptr;
// 		}
// 
// 		GST_BUFFER_PTS(gstBuffer) = blockTime;
// 		GST_BUFFER_DTS(gstBuffer) = blockTime;
// 		GST_BUFFER_DURATION(gstBuffer) = 0;
// 		GST_BUFFER_OFFSET(gstBuffer) = GST_BUFFER_OFFSET_NONE;
// 		GST_BUFFER_OFFSET_END(gstBuffer) = GST_BUFFER_OFFSET_NONE;
// 
// 		m_lastGetDataTime = blockTime;
// 
// 		m_vectorLock[m_indexBufNow]->unlock();
// 		m_indexBufNow++;
// 		m_indexBufNow %= m_buffers;
// 	}
// 	else
// 	{
// 		m_vectorLock[m_indexBufNow]->unlock();
// 	}
// 
// 	return gstBuffer;
// }