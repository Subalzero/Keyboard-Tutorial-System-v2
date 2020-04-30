#include "stdafx.h"
#include "Lessons3.h"

rescan::Lesson21::Lesson21(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 21)
{
}

void rescan::Lesson21::SpeakCurrentItem()
{
	if (index >= 15)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson21::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT27), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson22::Lesson22(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 22)
{
}

void rescan::Lesson22::SpeakCurrentItem()
{
	if (index >= 22)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson22::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT28), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson23::Lesson23(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 23)
{
}

void rescan::Lesson23::SpeakCurrentItem()
{
	if (index >= 18)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson23::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT29), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson24::Lesson24(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 24)
{
}

void rescan::Lesson24::SpeakCurrentItem()
{
	if (index >= 41)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson24::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT30), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson25::Lesson25(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 25)
{
}

void rescan::Lesson25::SpeakCurrentItem()
{
	if (index >= 29)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson25::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT31), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson26::Lesson26(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 26)
{
}

void rescan::Lesson26::SpeakCurrentItem()
{
	if (index >= 16)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson26::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT32), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson27::Lesson27(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 27)
{
}

void rescan::Lesson27::SpeakCurrentItem()
{
	if (index >= 17)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson27::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT33), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson28::Lesson28(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 28)
{
}

void rescan::Lesson28::SpeakCurrentItem()
{
	if (index >= 31)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson28::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT34), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson29::Lesson29(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 29)
{
}

void rescan::Lesson29::SpeakCurrentItem()
{
	if (index >= 16)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson29::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT35), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}

rescan::Lesson30::Lesson30(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 30)
{
}

void rescan::Lesson30::SpeakCurrentItem()
{
	if (index >= 25)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson30::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT36), L"TEXT", &size, &data);
	std::stringstream stream;
	stream.write(data, size);
	while (!stream.eof())
	{
		std::string s;
		safeGetline(stream, s);
		if (s.empty())
			continue;
		std::wstring ws(s.begin(), s.end());
		itemList.push_back(ws);
	}
}
