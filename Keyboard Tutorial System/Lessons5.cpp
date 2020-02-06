#include "stdafx.h"
#include "Lessons5.h"

rescan::Lesson41::Lesson41(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 41)
{
}

void rescan::Lesson41::SpeakCurrentItem()
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

void rescan::Lesson41::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT41), L"TEXT", &size, &data);
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

rescan::Lesson42::Lesson42(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 42)
{
}

void rescan::Lesson42::SpeakCurrentItem()
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

void rescan::Lesson42::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT42), L"TEXT", &size, &data);
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

rescan::Lesson43::Lesson43(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 43)
{
}

void rescan::Lesson43::SpeakCurrentItem()
{
	if (index >= 0)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

void rescan::Lesson43::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT43), L"TEXT", &size, &data);
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
