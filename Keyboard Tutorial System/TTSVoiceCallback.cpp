#include "stdafx.h"
#include "TTSVoiceCallback.h"

rescan::TTSVoiceCallback::TTSVoiceCallback() :
	nBuffers(0),
	hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL))
{
}

rescan::TTSVoiceCallback::~TTSVoiceCallback()
{
	CloseHandle(hBufferEndEvent);
}

void __stdcall rescan::TTSVoiceCallback::OnBufferEnd(void* pBufferContext)
{
	std::deque<unsigned char*>* buffers = (std::deque<unsigned char*>*)pBufferContext;
	ThreadSafePop(*buffers);
	if (nBuffers > 0)
		--nBuffers;
	if (nBuffers == 0)
		SetEvent(hBufferEndEvent);
}

void __stdcall rescan::TTSVoiceCallback::OnStreamEnd()
{
}

void __stdcall rescan::TTSVoiceCallback::OnVoiceProcessingPassEnd()
{
}

void __stdcall rescan::TTSVoiceCallback::OnVoiceProcessingPassStart(UINT32 SamplesRequired)
{
}

void __stdcall rescan::TTSVoiceCallback::OnBufferStart(void* pBufferContext)
{
}

void __stdcall rescan::TTSVoiceCallback::OnLoopEnd(void* pBufferContext)
{
}

void __stdcall rescan::TTSVoiceCallback::OnVoiceError(void* pBufferComtext, HRESULT Error)
{
}
