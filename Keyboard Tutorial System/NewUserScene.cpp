#include "stdafx.h"
#include "NewUserScene.h"

rescan::NewUserScene::NewUserScene(Rect rect, Graphics2D* gfx, Keyboard* kbd, TextToSpeech* tts) :
	Scene(rect, gfx), tts(tts), kbd(kbd)
{
	HRESULT hr = S_OK;
	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pWhiteBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&pBlackBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);
	
	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		PixelsToDIP(65.f),
		L"en-us",
		&pTitleTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		PixelsToDIP(65.f),
		L"en-us",
		&pTextFieldTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTitleTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFieldTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFieldTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	RECT rc = { 0 };
	GetClientRect(pGraphics->GetWindow(), &rc);
	scale = (double(rc.bottom) - double(rc.top)) / 1080;
}

rescan::NewUserScene::~NewUserScene()
{
}

void rescan::NewUserScene::Draw()
{
	RECT rect = { 0 };
	GetClientRect(pGraphics->GetWindow(), &rect);

	D2D1_RECT_F titleRect = {
		PixelsToDIP(rect.left),
		PixelsToDIP(rect.top + 125.f * scale),
		PixelsToDIP(rect.right),
		PixelsToDIP(rect.top + 125.f * scale + 80.f)
	};

	D2D1_RECT_F textFieldRect = {
		PixelsToDIP(rect.left + 150.f * scale),
		PixelsToDIP(rect.bottom / 2.f),
		PixelsToDIP(rect.right - 150.f * scale),
		PixelsToDIP(rect.bottom / 2.f + 90.f)
	};

	D2D1_RECT_F charRect = {
		textFieldRect.left,
		textFieldRect.top,
		textFieldRect.left + PixelsToDIP(65.f),
		textFieldRect.top + PixelsToDIP(65.f)
	};

	// Draw starts here.
	pGraphics->GetRenderTarget()->DrawTextW(
		L"New User",
		8,
		pTitleTextFormat,
		titleRect,
		pWhiteBrush
	);

	pGraphics->GetRenderTarget()->FillRectangle(
		textFieldRect,
		pWhiteBrush
	);

	if (selectedChar == 0 && drawCursor)
	{
		// Draw the cursor.
		pGraphics->GetRenderTarget()->DrawLine(
			D2D1::Point2F(
				charRect.left,
				charRect.top
			),
			D2D1::Point2F(
				charRect.left,
				charRect.bottom + 20.f
			),
			pBlackBrush,
			PixelsToDIP(15.f)
		);
	}

	auto iterator = textFieldChars.begin();
	for (size_t i = 0; i < textFieldChars.size(); ++i, ++iterator)
	{
		if (i == selectedChar - 1 && drawCursor)
		{
			// Draw the cursor.
			pGraphics->GetRenderTarget()->DrawLine(
				D2D1::Point2F(
					charRect.right - 20.f,
					charRect.top
				),
				D2D1::Point2F(
					charRect.right - 20.f,
					charRect.bottom + 20.f
				),
				pBlackBrush,
				PixelsToDIP(15.f)
			);
		}
		CComPtr<IDWriteTextLayout> pTextLayout = nullptr;
		std::wstring ws(1, *iterator);
		HRESULT hr = pGraphics->GetDWriteFactory()->CreateTextLayout(
			ws.c_str(),
			1,
			pTextFieldTextFormat,
			PixelsToDIP(65.f),
			PixelsToDIP(65.f),
			&pTextLayout
		);
		if (SUCCEEDED(hr))
		{
			DWRITE_TEXT_METRICS textMetrics = { 0 };
			pTextLayout->GetMetrics(&textMetrics);
			float width = textMetrics.widthIncludingTrailingWhitespace;

			pGraphics->GetRenderTarget()->DrawTextLayout(
				D2D1::Point2F(
					charRect.left,
					charRect.top
				),
				pTextLayout,
				pBlackBrush
			);

			charRect.left += width;
			charRect.right += width;
		}
	}
}

void rescan::NewUserScene::Update(double deltaTime)
{
	if (timeCounter > 1.0f)
	{
		drawCursor = !drawCursor;
		timeCounter = 0;
	}
	else
		timeCounter += deltaTime;
}

void rescan::NewUserScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_RETURN:
		{
			NewUserSceneContext cont = { 0 };
			std::wstringstream wss;
			for (wchar_t ch : textFieldChars)
			{
				wss << ch;
			}
			cont.userName = wss.str();
			if (callback)
				callback->SceneHasEnded(this, &cont);
			kbd->DisableAutorepeat();
			return;
		}
		case VK_ESCAPE:
		{
			NewUserSceneContext cont = { 0 };
			cont.isExit = true;
			if (callback)
				callback->SceneHasEnded(this, &cont);
			kbd->DisableAutorepeat();
			return;
		}
		case VK_BACK:
		{
			if (textFieldChars.size() > 0 && selectedChar > 0)
			{
				auto iter = textFieldChars.begin();
				std::advance(iter, selectedChar - 1);
				auto temp = iter;
				if (temp != textFieldChars.begin())
				{
					--temp;
					SpeakChar(*temp);
				}
				textFieldChars.erase(iter);

				--selectedChar;
			}
			return;
		}
		case VK_RIGHT:
		{
			if (selectedChar < textFieldChars.size())
			{
				auto iter = textFieldChars.begin();
				std::advance(iter, selectedChar);
				SpeakChar(*iter);
				++selectedChar;
			}
			return;
		}
		case VK_LEFT:
		{
			if (selectedChar > 0)
			{
				auto iter = textFieldChars.begin();
				if (selectedChar - 2 < textFieldChars.size())
				{
					std::advance(iter, selectedChar - 2);
					SpeakChar(*iter);
				}
				--selectedChar;
			}
			return;
		}
		}
		while (auto opChar = kbd->ReadChar())
		{
			if (textFieldChars.size() > MAX_CHARACTERS)
				break;
			if (*opChar == '\b' || *opChar == '\n')
				continue;

			auto iterator = textFieldChars.begin();
			std::advance(iterator, selectedChar);
			textFieldChars.insert(iterator, *opChar);
			++selectedChar;
			SpeakChar(*opChar);
		}

	}
}

void rescan::NewUserScene::Begin()
{
	kbd->FlushChar();
	kbd->EnableAutorepeat();
	selectedChar = 0;
	textFieldChars = std::list<wchar_t>();
	tts->speak(L"Enter new username.", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::NewUserScene::SpeakChar(const wchar_t wch)
{
	std::wstringstream wss;
	if (wch == ' ')
	{
		std::wstringstream temp;
		auto rIter = textFieldChars.rbegin();
		++rIter;
		while (rIter != textFieldChars.rend())
		{
			if (*rIter == ' ')
				break;
			temp << *rIter;
			++rIter;
		}
		std::wstring tempws = temp.str();
		std::wstring ws(tempws.rbegin(), tempws.rend());
		wss << ws;
	}
	else
		wss << wch;
	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}
