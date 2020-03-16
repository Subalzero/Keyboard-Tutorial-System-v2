#include "stdafx.h"
#include "IntroLessons.h"

rescan::Introduction1::Introduction1(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, gfx, kbd, mouse, tts, -1), kbd(kbd)
{
	HRESULT hr = S_OK;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	float ratio = (float(rc.bottom) - float(rc.top)) / 1080;

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		70.0 * ratio,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	this->tts = std::make_unique<TextToSpeech>(SPCAT_VOICES_ONECORE, 1);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

rescan::Introduction1::~Introduction1()
{
}

void rescan::Introduction1::Begin()
{
	ILesson::Begin();
}

void rescan::Introduction1::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	
	D2D1_RECT_F rect = {
		PixelsToDIP(rc.left),
		PixelsToDIP(rc.top),
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->DrawTextW(
		itemList[index].c_str(),
		itemList[index].length(),
		pTextFormat,
		rect,
		pWhiteBrush
	);
}

void rescan::Introduction1::Update(double deltaTime)
{
	ILesson::Update(deltaTime);
}

void rescan::Introduction1::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		while (const auto ch = kbd->ReadChar())
		{
			SpeakChar(*ch);
		}
		switch (ev.GetCode())
		{
		case VK_UP:
			tts->speak(L"Up", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			if (index == 0)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECHECK),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++index;
				SpeakCurrentItem();
				return;
			}
			break;
		case VK_DOWN:
			tts->speak(L"Down", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			if (index == 1)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECHECK),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++index;
				SpeakCurrentItem();
				return;
			}
			break;
		case VK_LEFT:
			tts->speak(L"Left", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			if (index == 2)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECHECK),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++index;
				SpeakCurrentItem();
				return;
			}
			break;
		case VK_RIGHT:
			tts->speak(L"Right", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			if (index == 3)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECHECK),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++index;
				SpeakCurrentItem();
				return;
			}
			break;
		case VK_RETURN:
			if (index == 4)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECOMPLETE),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				LessonContext cont = { 0 };
				cont.isTutorial = true;
				cont.lesson = lesson;
				if (callback)
					callback->SceneHasEnded(this, &cont);
				return;
			}
			break;
		}

		PlaySound(
			MAKEINTRESOURCE(IDR_WAVEWRONG),
			GetModuleHandle(NULL),
			SND_RESOURCE | SND_ASYNC
		);
	}
}

void rescan::Introduction1::SpeakCurrentItem()
{
	tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::Introduction1::LoadLessons()
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

void rescan::Introduction1::SayHint()
{
}

rescan::Introduction2::Introduction2(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, gfx, kbd, mouse, tts, -2), kbd(kbd)
{
	HRESULT hr = S_OK;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	float ratio = (float(rc.bottom) - float(rc.top)) / 1080;

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		70.0 * ratio,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	this->tts = std::make_unique<TextToSpeech>(SPCAT_VOICES_ONECORE, 1);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

rescan::Introduction2::~Introduction2()
{
}

void rescan::Introduction2::Begin()
{
	ILesson::Begin();
}

void rescan::Introduction2::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);

	D2D1_RECT_F rect = {
		PixelsToDIP(rc.left),
		PixelsToDIP(rc.top),
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->DrawTextW(
		itemList[index].c_str(),
		itemList[index].length(),
		pTextFormat,
		rect,
		pWhiteBrush
	);
}

void rescan::Introduction2::Update(double deltaTime)
{
	ILesson::Update(deltaTime);
}

void rescan::Introduction2::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		while (const auto ch = kbd->ReadChar())
		{
			SpeakChar(*ch);
		}
		switch (ev.GetCode())
		{
		case VK_CONTROL:
			tts->speak(L"Control", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			if (index == 0)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECHECK),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++index;
				SpeakCurrentItem();
				return;
			}
			break;
		case VK_SPACE:
			if (index == 1)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECOMPLETE),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				LessonContext cont = { 0 };
				cont.isTutorial = true;
				cont.lesson = lesson;
				if (callback)
					callback->SceneHasEnded(this, &cont);
				return;
			}
			break;
		}

		PlaySound(
			MAKEINTRESOURCE(IDR_WAVEWRONG),
			GetModuleHandle(NULL),
			SND_RESOURCE | SND_ASYNC
		);
	}
}

void rescan::Introduction2::SpeakCurrentItem()
{
	tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::Introduction2::LoadLessons()
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

void rescan::Introduction2::SayHint()
{
}

rescan::Introduction3::Introduction3(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, gfx, kbd, mouse, tts, -3), kbd(kbd)
{
	HRESULT hr = S_OK;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	float ratio = (float(rc.bottom) - float(rc.top)) / 1080;

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		70.0 * ratio,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	this->tts = std::make_unique<TextToSpeech>(SPCAT_VOICES_ONECORE, 1);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

rescan::Introduction3::~Introduction3()
{
}

void rescan::Introduction3::Begin()
{
	ILesson::Begin();
}

void rescan::Introduction3::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);

	D2D1_RECT_F rect = {
		PixelsToDIP(rc.left),
		PixelsToDIP(rc.top),
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->DrawTextW(
		itemList[index].c_str(),
		itemList[index].length(),
		pTextFormat,
		rect,
		pWhiteBrush
	);
}

void rescan::Introduction3::Update(double deltaTime)
{
	ILesson::Update(deltaTime);
}

void rescan::Introduction3::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		while (const auto ch = kbd->ReadChar())
		{
			SpeakChar(*ch);
		}
		switch (ev.GetCode())
		{
		case VK_ESCAPE:
			if (index == 0)
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVECOMPLETE),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				LessonContext cont = { 0 };
				cont.isTutorial = true;
				cont.lesson = lesson;
				if (callback)
					callback->SceneHasEnded(this, &cont);
				return;
			}
			break;
		}

		PlaySound(
			MAKEINTRESOURCE(IDR_WAVEWRONG),
			GetModuleHandle(NULL),
			SND_RESOURCE | SND_ASYNC
		);
	}
}

void rescan::Introduction3::SpeakCurrentItem()
{
	tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::Introduction3::LoadLessons()
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

void rescan::Introduction3::SayHint()
{
}

rescan::Introduction4::Introduction4(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, -4)
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

void rescan::Introduction4::LoadLessons()
{
}

void rescan::Introduction4::SpeakCurrentItem()
{
	if (index == 0)
	{
		tts->speak(L"F and J keys is used to navigate the keyboard. place your left index finger to the F key and press it once",
			TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else if (index == 1)
	{
		tts->speak(L"place your right index finger to the J key and press it once", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}

rescan::Introduction5::Introduction5(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, -5)
{
}

void rescan::Introduction5::LoadLessons()
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

void rescan::Introduction5::SpeakCurrentItem()
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

rescan::Introduction6::Introduction6(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts) :
	ILesson(rect, graphics, kbd, mouse, tts, -6)
{
}

void rescan::Introduction6::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress() && index == 0)
	{
		if (ev.GetCode() == VK_SHIFT && index == 0)
		{
			PlaySound(
				MAKEINTRESOURCE(IDR_WAVECHECK),
				GetModuleHandle(NULL),
				SND_RESOURCE | SND_ASYNC
			);
			++index;
			SpeakCurrentItem();
			return;
		}
		else
		{
			PlaySound(
				MAKEINTRESOURCE(IDR_WAVEWRONG),
				GetModuleHandle(NULL),
				SND_RESOURCE | SND_ASYNC
			);
		}
	}
	else
	{
		ILesson::KeyboardEvents(ev);
	}
}

void rescan::Introduction6::LoadLessons()
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

void rescan::Introduction6::SpeakCurrentItem()
{
	if (index == 0)
	{
		tts->speak(itemList[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		SayHint();
	}
}
