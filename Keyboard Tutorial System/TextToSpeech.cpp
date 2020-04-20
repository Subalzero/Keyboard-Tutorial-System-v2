#include "stdafx.h"
#include "TextToSpeech.h"

rescan::TextToSpeech::TextToSpeech(const wchar_t* source, unsigned voiceToken) :
	m_pMasterVoice(nullptr),
	m_pSourceVoice(nullptr),
	m_prevFlags(TTSFLAGS_DEFAULT)
{
	HRESULT hr;
	try
	{
		hr = m_format.AssignFormat(SPSF_22kHz16BitMono);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error assigning format.");
		hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_cpVoice);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing voice object.");
		hr = SpEnumTokens(source, NULL, NULL, &m_cpEnum);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error enumerating voices.");
		hr = m_cpEnum->Item(voiceToken, &m_cpVoiceToken);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error setting voice.");
		hr = m_cpStream.CoCreateInstance(CLSID_SpStream);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing stream object.");
		hr = CreateStreamOnHGlobal(NULL, TRUE, &m_cpBaseStream);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing base stream object.");
		hr = m_cpStream->SetBaseStream(m_cpBaseStream, m_format.m_guidFormatId, m_format.WaveFormatExPtr());
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error setting base stream.");
		hr = m_cpVoice->SetOutput(m_cpStream, TRUE);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error setting output stream.");
		hr = m_cpVoice->SetVoice(m_cpVoiceToken);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error setting voice.");
		hr = XAudio2Create(&m_cpXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing XAudio2.");
		hr = m_cpXAudio2->CreateMasteringVoice(&m_pMasterVoice);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error creating mastering voice.");
		hr = m_cpXAudio2->CreateSourceVoice(&m_pSourceVoice, m_format.WaveFormatExPtr(), 0, XAUDIO2_DEFAULT_FREQ_RATIO, &m_callback);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error creating source voice.");

		m_cpVoice->SetRate(-1);
	}
	catch (std::exception& e)
	{
		ShowCursor(TRUE);
		MessageBoxA(NULL, e.what(), "Fatal Error", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

rescan::TextToSpeech::~TextToSpeech()
{
	if (m_pSourceVoice)
	{
		m_pSourceVoice->Stop();
		m_pSourceVoice->DestroyVoice();
		m_pSourceVoice = nullptr;
	}
	if (m_pMasterVoice)
	{
		m_pMasterVoice->DestroyVoice();
		m_pMasterVoice = nullptr;
	}
	while (!m_buffers.empty())
	{
		unsigned char* pData = m_buffers.front();
		m_buffers.pop_front();
		delete[] pData;
	}
}

void rescan::TextToSpeech::speak(const wchar_t* str, int flags)
{
	std::lock_guard lock(mut);
	// Clear all.
	if (flags & TTSFLAGS_PURGEBEFORESPEAK)
	{
		m_pSourceVoice->Stop();
		m_pSourceVoice->FlushSourceBuffers();
		Sleep(10);
		while (!m_buffers.empty())
			ThreadSafePop(m_buffers);
		m_callback.nBuffers = 0;
	}
	m_cpStream.Release();
	m_cpBaseStream.Release();
	// Reset streams.
	try
	{
		HRESULT hr;
		hr = m_cpStream.CoCreateInstance(CLSID_SpStream);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing stream object.");
		hr = CreateStreamOnHGlobal(NULL, TRUE, &m_cpBaseStream);
		if (FAILED(hr))
			throw std::runtime_error("Rescan Text-to-Speech Error: Error initializing base stream object.");
	}
	catch (std::exception& e)
	{
		ShowCursor(TRUE);
		MessageBoxA(NULL, e.what(), "Fatal Error", MB_OK | MB_ICONERROR);
		exit(-1);
	}
	m_cpStream->SetBaseStream(m_cpBaseStream, m_format.m_guidFormatId, m_format.WaveFormatExPtr());
	m_cpVoice->SetOutput(m_cpStream, TRUE);
	// Make the TTS speak.
	if (flags & TTSFLAGS_IS_XML)
		m_cpVoice->Speak(str, SPF_DEFAULT | SPF_IS_XML, NULL);
	else
		m_cpVoice->Speak(str, SPF_DEFAULT, NULL);
	// Rewind the stream.
	LARGE_INTEGER li = { 0 };
	m_cpStream->Seek(li, STREAM_SEEK_SET, NULL);
	// Get base stream.
	IStream* pIStream;
	m_cpStream->GetBaseStream(&pIStream);
	// Get stream size.
	STATSTG stat;
	pIStream->Stat(&stat, STATFLAG_NONAME);
	ULONGLONG sSize = stat.cbSize.QuadPart;
	// Copy byte data to be processed.
	unsigned char* pData = new unsigned char[sSize];
	ULONG bytesRead;
	pIStream->Read((void*)pData, sSize, &bytesRead);
	pIStream->Release();
	// Put byte data to container.
	m_buffers.push_back(pData);
	// Remove Silence.
	size_t skip = 0;
	for (size_t i = 0; i < sSize; ++i)
	{
		if (pData[i] != 0)
			break;
		++skip;
	}
	// Set XAudio2 buffer.
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.AudioBytes = (UINT32)(sSize - skip);
	buffer.pAudioData = (const byte*)(pData + skip);
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.pContext = (void*)&m_buffers;
	// Submit the buffer.
	m_pSourceVoice->SubmitSourceBuffer(&buffer);
	++m_callback.nBuffers;
	// Reset event.
	if (m_prevFlags & TTSFLAGS_ASYNC)
		ResetEvent(m_callback.hBufferEndEvent);
	// Start playing.
	m_pSourceVoice->Start();
	if (!(flags & TTSFLAGS_ASYNC))
		WaitForSingleObject(m_callback.hBufferEndEvent, INFINITE);
	m_prevFlags = flags;
}

void rescan::TextToSpeech::stop()
{
	m_pSourceVoice->Stop();
	while (!m_buffers.empty())
		ThreadSafePop(m_buffers);
	m_pSourceVoice->FlushSourceBuffers();
	m_callback.nBuffers = 0;
}

void rescan::TextToSpeech::pause()
{
	m_pSourceVoice->Stop();
}

void rescan::TextToSpeech::resume()
{
	m_pSourceVoice->Start();
}

