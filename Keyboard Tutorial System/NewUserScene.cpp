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
		65.f,
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
		65.f,
		L"en-us",
		&pTextFieldTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTitleTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFieldTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFieldTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

rescan::NewUserScene::~NewUserScene()
{
}

void rescan::NewUserScene::Draw()
{
}

void rescan::NewUserScene::Update(double deltaTime)
{
}

void rescan::NewUserScene::KeyboardEvents(const Keyboard::Event& ev)
{
}

void rescan::NewUserScene::Begin()
{
}
