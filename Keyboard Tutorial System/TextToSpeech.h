#pragma once

#pragma warning(disable : 4996)

#include "TTSVoiceCallback.h"
#include <sapi.h>
#include <sphelper.h>
#include <atlbase.h>
#include <exception>
#include <stdexcept>

#define SPCAT_VOICES_ONECORE L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices"
#define SPCAT_VOICES_DEFAULT SPCAT_VOICES

namespace rescan
{
	enum TextToSpeechFlags
	{
		TTSFLAGS_DEFAULT = 0,
		TTSFLAGS_ASYNC = 1,
		TTSFLAGS_PURGEBEFORESPEAK = 2,
		TTSFLAGS_IS_XML = 4
	};

	class TextToSpeech
	{
	public:
		// Constructor.
		TextToSpeech(const wchar_t* source = SPCAT_VOICES_DEFAULT, unsigned voiceToken = 0);
		// Destructor.
		~TextToSpeech();

		void speak(const wchar_t* str, int flags);
		void stop();
		void pause();
		void resume();

	private:
		TTSVoiceCallback m_callback;
		std::deque<unsigned char*> m_buffers;

		CComPtr<ISpVoice> m_cpVoice;
		CComPtr<ISpStream> m_cpStream;
		CComPtr<ISpObjectToken> m_cpVoiceToken;
		CComPtr<IEnumSpObjectTokens> m_cpEnum;
		CComPtr<IStream> m_cpBaseStream;
		CComPtr<IXAudio2> m_cpXAudio2;
		IXAudio2MasteringVoice* m_pMasterVoice;
		IXAudio2SourceVoice* m_pSourceVoice;
		CSpStreamFormat m_format;

		std::mutex mut;

		int m_prevFlags;
	};

}
