#pragma once

#include <xaudio2.h>
#include <deque>
#include "Utils.h"

namespace rescan
{
	class TTSVoiceCallback :
		public IXAudio2VoiceCallback
	{
	public:
		// Constructor.
		TTSVoiceCallback();
		// Destructor.
		~TTSVoiceCallback();

		// Called when the voice has just finished playing a buffer audio stream.
		void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);

		// Unused methods are stubs.
		void STDMETHODCALLTYPE OnStreamEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired);
		void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext);
		void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext);
		void STDMETHODCALLTYPE OnVoiceError(void* pBufferComtext, HRESULT Error);

	public:
		HANDLE hBufferEndEvent;
		volatile unsigned nBuffers;

	};
}

