#include "stdafx.h"
#include "QuitMessageScene.h"

rescan::QuitMessageScene::QuitMessageScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts) :
	Scene(rect, gfx), tts(tts)
{
	HRESULT hr;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Aquamarine),
		&pSelectedTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		150.f,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		150.f,
		L"en-us",
		&pSelectedTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pSelectedTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pSelectedTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

rescan::QuitMessageScene::~QuitMessageScene()
{
}

void rescan::QuitMessageScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
			isOKSelected = !isOKSelected;
			if (isOKSelected)
				tts->speak(L"Ok", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			else
				tts->speak(L"Cancel", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			break;
		case VK_RETURN:
		{
			QuitMessageSceneContext context = { 0 };
			context.returnType = isOKSelected ? Type::QuitMessageScene_OK : Type::QuitMessageScene_CANCEL;
			if (callback)
				callback->SceneHasEnded(this, &context);
			break;
		}
		case VK_ESCAPE:
		{
			QuitMessageSceneContext context = { 0 };
			context.returnType = Type::QuitMessageScene_CANCEL;
			if (callback)
				callback->SceneHasEnded(this, &context);
			break;
		}
		}
	}
}

void rescan::QuitMessageScene::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	D2D1_RECT_F questionRect = {
		PixelsToDIP(rc.left),
		PixelsToDIP(rc.bottom / 3.f) - 150.f,
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom / 3.f)
	};

	D2D1_RECT_F okRect = {
		PixelsToDIP(rc.left + 100.f),
		PixelsToDIP(2 * rc.bottom / 3.f),
		PixelsToDIP(rc.right / 2.f),
		PixelsToDIP(rc.bottom)
	};

	D2D1_RECT_F cancelRect = {
		PixelsToDIP(rc.right / 2.f),
		PixelsToDIP(2 * rc.bottom / 3.f),
		PixelsToDIP(rc.right - 100.f),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->DrawTextW(
		L"Do you want to quit?",
		20,
		pTextFormat.Get(),
		questionRect,
		pTextBrush.Get()
	);

	if (isOKSelected)
	{
		pGraphics->GetRenderTarget()->DrawTextW(
			L"OK",
			2,
			pSelectedTextFormat.Get(),
			okRect,
			pSelectedTextBrush.Get()
		);

		pGraphics->GetRenderTarget()->DrawTextW(
			L"Cancel",
			6,
			pTextFormat.Get(),
			cancelRect,
			pTextBrush.Get()
		);
	}
	else
	{
		pGraphics->GetRenderTarget()->DrawTextW(
			L"OK",
			2,
			pTextFormat.Get(),
			okRect,
			pTextBrush.Get()
		);

		pGraphics->GetRenderTarget()->DrawTextW(
			L"Cancel",
			6,
			pSelectedTextFormat.Get(),
			cancelRect,
			pSelectedTextBrush.Get()
		);
	}
}

void rescan::QuitMessageScene::Update(double deltaTime)
{
}

void rescan::QuitMessageScene::Begin()
{
	isOKSelected = false;
	tts->speak(L"Do you want to quit?", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}
