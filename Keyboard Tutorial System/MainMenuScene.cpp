#include "stdafx.h"
#include "MainMenuScene.h"

rescan::MainMenuScene::MainMenuScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts, Keyboard* kbd) :
	Scene(rect, gfx), tts(tts), index(0), kbd(kbd)
{
	HRESULT hr;

	hr = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(0x1D00AC),
		&pTitleBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pSelectedTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pUpperRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightGray),
		&pCenterRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		45.f,
		L"en-us",
		&pTitleFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = gfx->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		100.f,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTitleFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTitleFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	options.push_back(L"Start");
	options.push_back(L"Exit");
}

rescan::MainMenuScene::~MainMenuScene()
{
}

void rescan::MainMenuScene::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);

	//std::wstringstream wss;
	//wss << L"Left: " << rc.left
		//<< L" Top: " << rc.top
		//<< L" Right: " << rc.right
		//<< L" Bottom: " << rc.bottom << std::endl;
	//OutputDebugString(wss.str().c_str());

	D2D1_RECT_F upperRect = {
		0.f,
		0.f,
		PixelsToDIP(rc.right),
		PixelsToDIP(100.f)
	};

	D2D1_RECT_F centerRect = {
		0.f,
		PixelsToDIP(100.f),
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom)
	};

	D2D1_RECT_F titleRect = {
		0.f,
		0.f,
		PixelsToDIP(480.f),
		PixelsToDIP(100.f)
	};

	D2D1_RECT_F menuTextRect = {
		PixelsToDIP(rc.right / 3.f),
		PixelsToDIP(rc.bottom / 2.f),
		PixelsToDIP(2 * rc.right / 3.f),
		PixelsToDIP(rc.bottom / 2.f + 100.f)
	};

	// Draw start
	pGraphics->GetRenderTarget()->FillRectangle(
		upperRect,
		pUpperRectBrush
	);

	pGraphics->GetRenderTarget()->FillRectangle(
		centerRect,
		pCenterRectBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		L"rescan-act",
		10,
		pTitleFormat,
		titleRect,
		pTitleBrush
	);

	for (size_t i = 0; i < options.size(); ++i) {
		if (i == index)
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				options[i].c_str(),
				options[i].length(),
				pTextFormat,
				menuTextRect,
				pSelectedTextBrush
			);
		}
		else
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				options[i].c_str(),
				options[i].length(),
				pTextFormat,
				menuTextRect,
				pTextBrush
			);
		}
		
		menuTextRect.top += 100.f;
		menuTextRect.bottom += 100.f;
	}
}

void rescan::MainMenuScene::Update(double deltaTime)
{

}

void rescan::MainMenuScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_ESCAPE:
		{
			MainMenuSceneContext cont = { 0 };
			cont.index = index;
			cont.isExit = true;
			if (callback)
				callback->SceneHasEnded(this, &cont);
			break;
		}
		case VK_UP:
		{
			Up();
			break;
		}
		case VK_DOWN:
		{
			Down();
			break;
		}
		case VK_RETURN:
		{
			MainMenuSceneContext cont = { 0 };
			cont.index = index;
			if (callback)
				callback->SceneHasEnded(this, &cont);
			break;
		}
		}
	}
}

void rescan::MainMenuScene::Begin()
{
	index = 0;
	tts->speak(L"Welcome! Please use the up and down keys to choose.", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::MainMenuScene::Up()
{
	if (--index >= options.size())
	{
		index = options.size() - 1;
	}
	tts->speak(options[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::MainMenuScene::Down()
{
	if (++index >= options.size())
	{
		index = 0;
	}
	tts->speak(options[index].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}
