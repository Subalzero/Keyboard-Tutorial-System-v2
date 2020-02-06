#include "stdafx.h"
#include "Lessons4.h"

rescan::Lesson31::Lesson31(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 31)
{
}

void rescan::Lesson31::SpeakCurrentItem()
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

void rescan::Lesson31::LoadLessons()
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

rescan::Lesson32::Lesson32(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 32)
{
}

void rescan::Lesson32::SpeakCurrentItem()
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

void rescan::Lesson32::LoadLessons()
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

rescan::Lesson33::Lesson33(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 33)
{
}

void rescan::Lesson33::SpeakCurrentItem()
{
	if (index >= 20)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson33::LoadLessons()
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

rescan::Lesson34::Lesson34(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 34)
{
}

void rescan::Lesson34::SpeakCurrentItem()
{
	if (index >= 12)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson34::LoadLessons()
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

rescan::Lesson35::Lesson35(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 35)
{
}

void rescan::Lesson35::SpeakCurrentItem()
{
	if (index >= 9)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson35::LoadLessons()
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

rescan::Lesson36::Lesson36(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 36)
{
}

void rescan::Lesson36::SpeakCurrentItem()
{
	if (index >= 20)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson36::LoadLessons()
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

rescan::Lesson37::Lesson37(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 37)
{
}

void rescan::Lesson37::SpeakCurrentItem()
{
	{
		SayHint();
	}
}

void rescan::Lesson37::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT37), L"TEXT", &size, &data);
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

rescan::Lesson38::Lesson38(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 38)
{
}

void rescan::Lesson38::SpeakCurrentItem()
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

void rescan::Lesson38::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT38), L"TEXT", &size, &data);
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

rescan::Lesson39::Lesson39(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 39)
{
}

void rescan::Lesson39::SpeakCurrentItem()
{
	if (index >= 19)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson39::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT39), L"TEXT", &size, &data);
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

rescan::Lesson40::Lesson40(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 40)
{
}

void rescan::Lesson40::SpeakCurrentItem()
{
	if (index >= 21)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson40::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT40), L"TEXT", &size, &data);
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
