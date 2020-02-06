#include "stdafx.h"
#include "ScoreScene.h"

rescan::ScoreScene::ScoreScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts) :
	Scene(rect, gfx),
	rectHeight(0),
	callback(nullptr),
	tts(tts),
	WPM(0),
	accuracy(0),
	time(0),
	opacity(0)
{
	HRESULT hr;
	
	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::OrangeRed),
		&pRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		55.f,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		65.f,
		L"en-us",
		&pBigTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pBigTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pBigTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	pTextBrush->SetOpacity(opacity);
}

rescan::ScoreScene::~ScoreScene()
{
}

void rescan::ScoreScene::Begin()
{
	rectHeight = 0;
	opacity = 0;
}

void rescan::ScoreScene::End()
{
}

void rescan::ScoreScene::Draw()
{
	std::wstringstream ws1, ws2;
	ws1 << timeWStr;
	ws2 << accuracyWStr << L"%";
	RECT rect;
	GetClientRect(pGraphics->GetWindow(), &rect);
	std::wstringstream wss;
	rect.left = PixelsToDIP(rect.left);
	rect.top = PixelsToDIP(rect.top);
	rect.right = PixelsToDIP(rect.right);
	rect.bottom = PixelsToDIP(rect.bottom);
	D2D1_RECT_F timeTextRect = { 0.f, 500.f, rect.right / 3.f, 555.f };
	D2D1_RECT_F wpmTextRect = { rect.right / 3.0f, 500.f, 2 * rect.right / 3.f, 555.f };
	D2D1_RECT_F accTextRect = { 2 * rect.right / 3.f, 500.f, (float)rect.right, 555.f };
	D2D1_RECT_F bigTextRect = { 0.0f, 425.0f, rect.right / 3.0f, 500.0f };
	D2D1_RECT_F wpmbigTextRect = { rect.right / 3.0f, 425.0f, 2.f * rect.right / 3.0f, 500.0f };
	D2D1_RECT_F accbigTextRect = { 2.f * rect.right / 3.0f, 425.0f, (float)rect.right, 500.0f };

	pGraphics->GetRenderTarget()->DrawTextW(
		ws1.str().c_str(),
		ws1.str().length(),
		pBigTextFormat,
		bigTextRect,
		pTextBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		L"Time (sec)",
		10,
		pTextFormat,
		timeTextRect,
		pTextBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		WPMWStr.c_str(),
		WPMWStr.length(),
		pBigTextFormat,
		wpmbigTextRect,
		pTextBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		L"WPM",
		3,
		pTextFormat,
		wpmTextRect,
		pTextBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		ws2.str().c_str(),
		ws2.str().length(),
		pBigTextFormat,
		accbigTextRect,
		pTextBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		L"Accuracy",
		8,
		pTextFormat,
		accTextRect,
		pTextBrush
	);
}

void rescan::ScoreScene::Update(double deltaTime)
{
	if (opacity < 1.f)
	{
		opacity += deltaTime * 0.5f;
		pTextBrush->SetOpacity(opacity);
	}
}

void rescan::ScoreScene::SetScore(double time, double wpm, double accuracy)
{
	this->time = time;
	this->WPM = wpm;
	this->accuracy = accuracy;

	std::wstringstream wstream1, wstream2, wstream3;
	wstream1 << std::lroundf(time);
	wstream1 >> timeWStr;
	wstream2 << std::lroundf(wpm);
	wstream2 >> WPMWStr;
	wstream3 << std::lroundf(accuracy);
	wstream3 >> accuracyWStr;

	std::wstringstream ws;
	ws << L"Lesson has ended. Your time is "
		<< timeWStr << L" seconds."
		<< L" Words per minute "
		<< WPMWStr << L"."
		<< L" Accuracy: "
		<< accuracyWStr << L" percent.";

	tts->speak(ws.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::ScoreScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_ESCAPE:
		case VK_RETURN:
			if (callback)
				callback->SceneHasEnded(this, NULL);
			break;
		}
	}
}
