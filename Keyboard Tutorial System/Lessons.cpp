#include "stdafx.h"
#include "Lessons.h"

//////////////////////////////////////////////
// LESSON 1
//////////////////////////////////////////////

rescan::Lesson1::Lesson1(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 1)
{
}

void rescan::Lesson1::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT1), L"TEXT", &size, &data);
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

void rescan::Lesson1::SpeakCurrentItem()
{
	if (index == 0)
	{
		tts->speak(
			L"Put your right index finger to the J key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index == 2)
	{
		tts->speak(
			L"Put your right middle finger to the K key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
		
	}
	else if (index == 4)
	{
		tts->speak(
			L"Put your right ring finger to the L key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index == 6)
	{
		tts->speak(
			L"Put your right pinky finger to the semi-colon key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else
	{
		SayHint();
	}
}

//////////////////////////////////////////////
// LESSON 2
//////////////////////////////////////////////


rescan::Lesson2::Lesson2(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 2)
{

}

void rescan::Lesson2::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT2), L"TEXT", &size, &data);
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

void rescan::Lesson2::SpeakCurrentItem()
{
	if (index == 0)
	{
		tts->speak(
			L"Put your left index finger to the F key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index == 2)
	{
		tts->speak(
			L"Put your left middle finger to the D key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index == 4)
	{
		tts->speak(
			L"Put your left ring finger to the S key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index == 6)
	{
		tts->speak(
			L"Put your left pinky finger to the A key and press it twice.",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK
		);
	}
	else if (index >= 20)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}


//////////////////////////////////////////////
// LESSON 3
//////////////////////////////////////////////


rescan::Lesson3::Lesson3(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 3)
{
}

void rescan::Lesson3::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT3), L"TEXT", &size, &data);
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

void rescan::Lesson3::SpeakCurrentItem()
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

//////////////////////////////////////////////
// LESSON 4
//////////////////////////////////////////////

rescan::Lesson4::Lesson4(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 4)
{
}

void rescan::Lesson4::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT4), L"TEXT", &size, &data);
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

void rescan::Lesson4::SpeakCurrentItem()
{
	if (index >= 21)
	{
		std::wstring ws(itemList[index]);
		if (index >= 38)
			ws.append(L" semi-colon");
		tts->speak(ws.c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

//////////////////////////////////////////////
// LESSON 5
//////////////////////////////////////////////


rescan::Lesson5::Lesson5(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 5)
{
}

void rescan::Lesson5::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT5), L"TEXT", &size, &data);
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

void rescan::Lesson5::SpeakCurrentItem()
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


//////////////////////////////////////////////
// LESSON 6
//////////////////////////////////////////////

rescan::Lesson6::Lesson6(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 6)
{
}

void rescan::Lesson6::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT6), L"TEXT", &size, &data);
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

void rescan::Lesson6::SpeakCurrentItem()
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

//////////////////////////////////////////////
// LESSON 7
//////////////////////////////////////////////

rescan::Lesson7::Lesson7(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 7)
{
}

void rescan::Lesson7::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT7), L"TEXT", &size, &data);
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

void rescan::Lesson7::SpeakCurrentItem()
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

//////////////////////////////////////////////
// LESSON 8
//////////////////////////////////////////////

rescan::Lesson8::Lesson8(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 8)
{
}

void rescan::Lesson8::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT8), L"TEXT", &size, &data);
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

void rescan::Lesson8::SpeakCurrentItem()
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

//////////////////////////////////////////////
// LESSON 9
//////////////////////////////////////////////

rescan::Lesson9::Lesson9(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 9)
{
}

void rescan::Lesson9::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT9), L"TEXT", &size, &data);
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

void rescan::Lesson9::SpeakCurrentItem()
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

//////////////////////////////////////////////
// LESSON 10
//////////////////////////////////////////////

rescan::Lesson10::Lesson10(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, 10)
{
}

void rescan::Lesson10::LoadLessons()
{
	const char* data;
	DWORD size;
	LoadFileInResource(MAKEINTRESOURCE(IDR_TEXT10), L"TEXT", &size, &data);
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

void rescan::Lesson10::SpeakCurrentItem()
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