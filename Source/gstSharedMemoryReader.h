#ifndef NEMO_GST_SHARED_MEMORY_READER_H
#define NEMO_GST_SHARED_MEMORY_READER_H

#include "../JuceLibraryCode/JuceHeader.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/thread/mutex.hpp>
#include <gst/gstbuffer.h>
#include <list>
#include <vector>

#include "nemoWindowGlobalMutex.h"

class gstSharedMemoryBin;

class gstSharedMemoryReader : public HighResolutionTimer
{
public:
	gstSharedMemoryReader();
	virtual ~gstSharedMemoryReader();

	bool openSharedMemory(String sharedMemoryName, int buffers, int bufferBlockSize);
	void closeSharedMemory();

	void hiResTimerCallback();

	GstBuffer* getGstBuffer();
protected:
	String m_fileName;
	int m_buffers;
	int m_bufferBlockSize;

	std::vector<nemoWindowGlobalMutex*> m_vectorLock;
	boost::interprocess::windows_shared_memory m_fileMem;
	boost::interprocess::mapped_region m_region;
	int m_indexBufNow;
	int64 m_lastGetDataTime;
	int64 m_beginTime;

	std::list<GstBuffer*> m_listGstBuffer;
	boost::mutex m_lockGstBuffer;
};

#endif