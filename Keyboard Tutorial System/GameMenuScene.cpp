#include "stdafx.h"
#include "GameMenuScene.h"
#include "Exception.h"

rescan::GameMenuScene::GameMenuScene(Rect frame, Graphics2D* graphics, Keyboard* kbd, TextToSpeech* tts) :
	Scene(frame, graphics),
	pArrowBrush(nullptr),
	pUpArrowPath(nullptr),
	pDownArrowPath(nullptr),
	pMenuRectBrush(nullptr),
	pTextBrush(nullptr),
	pSelectedTextBrush(nullptr),
	pSelectedArrowBrush(nullptr),
	pUpperRectBrush(nullptr),
	pSideRectBrush(nullptr),
	pTextFormat(nullptr),
	pTitleTextBrush(nullptr),
	pTitleTextFormat(nullptr),
	selected(0),
	keyboard(kbd),
	tts(tts)
{
	HRESULT hr;

	ID2D1HwndRenderTarget* pRT = graphics->GetRenderTarget();

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pSelectedTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightGray),
		&pMenuRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Green),
		&pArrowBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::YellowGreen),
		&pSelectedArrowBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pUpperRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(0x005fff),
		&pSideRectBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pRT->CreateSolidColorBrush(
		D2D1::ColorF(0x1D00AC),
		&pTitleTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	IDWriteFactory* pDWriteFactory = graphics->GetDWriteFactory();

	hr = pDWriteFactory->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		45.f,
		L"en-us",
		&pTitleTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	ID2D1Factory* pD2DFactory = graphics->GetD2DFactory();

	hr = pD2DFactory->CreatePathGeometry(
		&pUpArrowPath
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pD2DFactory->CreatePathGeometry(
		&pDownArrowPath
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pDWriteFactory->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		35.f,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	pTitleTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// Lesson Names.
	lessonList.push_back(L"Lesson 1: The Right Hand");
	lessonList.push_back(L"Lesson 2: The Left Hand");
	lessonList.push_back(L"Lesson 3: The Home Row");
	lessonList.push_back(L"Lesson 4: The I Key");
	lessonList.push_back(L"Lesson 5: The E Key");
	lessonList.push_back(L"Lesson 6: The H Key");
	lessonList.push_back(L"Lesson 7: The G Key");
	lessonList.push_back(L"Lesson 8: The R Key");
	lessonList.push_back(L"Lesson 9: The U Key");
	lessonList.push_back(L"Lesson 10: The N Key");
	lessonList.push_back(L"Lesson 11: The V Key");
	lessonList.push_back(L"Lesson 12: The W Key");
	lessonList.push_back(L"Lesson 13: The O Key");
	lessonList.push_back(L"Lesson 14: Capital Letters");
	lessonList.push_back(L"Lesson 15: C and Comma");
	lessonList.push_back(L"Lesson 16: T and Period");
	lessonList.push_back(L"Lesson 17: Question Mark");
	lessonList.push_back(L"Lesson 18: The M Key");
	lessonList.push_back(L"Lesson 19: The Y Key");
	lessonList.push_back(L"Lesson 20: Single Quote");
	lessonList.push_back(L"Lesson 21: The B Key");
	lessonList.push_back(L"Lesson 22: Double Quote");
	lessonList.push_back(L"Lesson 23: The Q Key");
	lessonList.push_back(L"Lesson 24: The Colon Key");
	lessonList.push_back(L"Lesson 25: The P Key");
	lessonList.push_back(L"Lesson 26: The X Key");
	lessonList.push_back(L"Lesson 27: The Z Key");
	lessonList.push_back(L"Lesson 28: Left Hand Number Row");
	lessonList.push_back(L"Lesson 29: Right Hand Number Row");
	lessonList.push_back(L"Lesson 30: The Entire Number Row");
	lessonList.push_back(L"Lesson 31: Exclamation Mark and @ Symbol");
	lessonList.push_back(L"Lesson 32: Number and Dollar Sign");
	lessonList.push_back(L"Lesson 33: Percent and Caret");
	lessonList.push_back(L"Lesson 34: Ampersand and Asterisk");
	lessonList.push_back(L"Lesson 35: Left and Right Parenthesis");
	lessonList.push_back(L"Lesson 36: Underscore and Hyphen");
	lessonList.push_back(L"Lesson 37: Equal and Plus");
	lessonList.push_back(L"Lesson 38: Square and Brackets");
	lessonList.push_back(L"Lesson 39: Curly Brackets");
	lessonList.push_back(L"Lesson 40: Less than and Greater than");
	lessonList.push_back(L"Lesson 41: Forward Slash and Backlash");
	lessonList.push_back(L"Lesson 42: Tilde and Grave Accent");
	lessonList.push_back(L"Lesson 43: Numpad");

	// Get Screen ratio relative to 1080p screen.
	RECT rect;
	GetClientRect(graphics->GetWindow(), &rect);
	float ratioX = ((float)rect.right - (float)rect.left) / (float)1920;
	float ratioY = ((float)rect.bottom - (float)rect.top) / (float)1080;

	// Draw the arrows.
	ID2D1GeometrySink* pSink = nullptr;
	hr = pUpArrowPath->Open(&pSink);
	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetClientRect(graphics->GetWindow(), &rc);
		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		pSink->BeginFigure(
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX),
				PixelsToDIP(275.f * ratioY)
			),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX + 15.f),
				PixelsToDIP(290.f * ratioY)
			),
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX - 15.f),
				PixelsToDIP(290.f * ratioY)
			)
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
	}

	if (pSink)
	{
		pSink->Release();
		pSink = nullptr;
	}

	hr = pDownArrowPath->Open(&pSink);

	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetClientRect(graphics->GetWindow(), &rc);
		pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		pSink->BeginFigure(
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX),
				PixelsToDIP(985.f * ratioY)
			),
			D2D1_FIGURE_BEGIN_FILLED
		);
		D2D1_POINT_2F points[] = {
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX + 15),
				PixelsToDIP(970.f * ratioY)
			),
			D2D1::Point2F(
				PixelsToDIP((rc.right - 480.f) * 0.5f * ratioX + 480.f * ratioX - 15),
				PixelsToDIP(970.f * ratioY)
			)
		};
		pSink->AddLines(points, ARRAYSIZE(points));
		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pSink->Close();
	}

	if (pSink)
	{
		pSink->Release();
		pSink = nullptr;
	}
}

rescan::GameMenuScene::~GameMenuScene()
{
	if (pTextBrush)
	{
		pTextBrush->Release();
		pTextBrush = nullptr;
	}
	if (pSelectedTextBrush)
	{
		pSelectedTextBrush->Release();
		pSelectedTextBrush = nullptr;
	}
	if (pTextFormat)
	{
		pTextFormat->Release();
		pTextFormat = nullptr;
	}
	if (pMenuRectBrush)
	{
		pMenuRectBrush->Release();
		pMenuRectBrush = nullptr;
	}
	if (pArrowBrush)
	{
		pArrowBrush->Release();
		pArrowBrush = nullptr;
	}
	if (pUpperRectBrush)
	{
		pUpperRectBrush->Release();
		pUpperRectBrush = nullptr;
	}
	if (pSideRectBrush)
	{
		pSideRectBrush->Release();
		pSideRectBrush = nullptr;
	}
	if (pTitleTextBrush)
	{
		pTitleTextBrush->Release();
		pTitleTextBrush = nullptr;
	}
	if (pTitleTextFormat)
	{
		pTitleTextFormat->Release();
		pTitleTextFormat = nullptr;
	}
	if (pUpArrowPath)
	{
		pUpArrowPath->Release();
		pUpArrowPath = nullptr;
	}
	if (pDownArrowPath)
	{
		pDownArrowPath->Release();
		pDownArrowPath = nullptr;
	}
	if (pSelectedArrowBrush)
	{
		pSelectedArrowBrush->Release();
		pSelectedArrowBrush = nullptr;
	}
}

void rescan::GameMenuScene::Draw()
{
	// Get Screen ratio relative to 1080p screen.
	RECT rect;
	GetClientRect(pGraphics->GetWindow(), &rect);
	float ratioX = ((float)rect.right - (float)rect.left) / (float)1920;
	float ratioY = ((float)rect.bottom - (float)rect.top) / (float)1080;
	RECT rc = {};
	GetClientRect(pGraphics->GetWindow(), &rc);
	rc.left = 480 * ratioX;
	rc.top = 100 * ratioY;
	D2D1_RECT_F menuSubtitleRect = {
		PixelsToDIP(50.f * ratioX + rc.left) ,
		PixelsToDIP(100.f * ratioY + rc.top),
		PixelsToDIP(rc.right - 50.f * ratioX),
		PixelsToDIP(135.f * ratioY + rc.top)
	};
	D2D1_RECT_F menuChoicesRect = {
		PixelsToDIP(100.f * ratioX + rc.left),
		PixelsToDIP(250.f * ratioY + rc.top),
		PixelsToDIP(rc.right - 100.f * ratioX),
		PixelsToDIP(285.f * ratioY)
	};
	D2D1_RECT_F menuFilledRect = {
		PixelsToDIP(rc.left),
		PixelsToDIP(rc.top),
		PixelsToDIP(rc.right),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->FillRectangle(
		menuFilledRect,
		pMenuRectBrush
	);

	pGraphics->GetRenderTarget()->FillGeometry(
		pUpArrowPath,
		pArrowBrush
	);

	pGraphics->GetRenderTarget()->FillGeometry(
		pDownArrowPath,
		pArrowBrush
	);

	if (keyboard->KeyIsPressed(VK_UP))
	{
		pGraphics->GetRenderTarget()->FillGeometry(
			pUpArrowPath,
			pSelectedArrowBrush
		);
	}

	if (keyboard->KeyIsPressed(VK_DOWN))
	{
		pGraphics->GetRenderTarget()->FillGeometry(
			pDownArrowPath,
			pSelectedArrowBrush
		);
	}

	pGraphics->GetRenderTarget()->DrawTextW(
		L"Choose A Lesson",
		wcslen(L"Choose A Lesson"),
		pTextFormat,
		menuSubtitleRect,
		pTextBrush
	);

	unsigned int j = (selected / 10) * 10;

	for (unsigned int i = 0; i < 10 && j < lessonList.size(); ++i, ++j)
	{
		if (j == selected)
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				lessonList[j].c_str(),
				lessonList[j].length(),
				pTextFormat,
				menuChoicesRect,
				pSelectedTextBrush
			);
		}
		else
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				lessonList[j].c_str(),
				lessonList[j].length(),
				pTextFormat,
				menuChoicesRect,
				pTextBrush
			);
		}
		menuChoicesRect.top += 55.f * ratioY;
		menuChoicesRect.bottom += 55.f * ratioY;
	}

	D2D1_RECT_F upperRect = {
		0.f,
		0.f,
		PixelsToDIP(rc.right),
		PixelsToDIP(100.f * ratioY)
	};

	pGraphics->GetRenderTarget()->FillRectangle(
		upperRect,
		pUpperRectBrush
	);

	D2D1_RECT_F sideRect = {
		0.f,
		PixelsToDIP(100.f * ratioY),
		PixelsToDIP(480.f * ratioX),
		PixelsToDIP(rc.bottom)
	};

	pGraphics->GetRenderTarget()->FillRectangle(
		sideRect,
		pSideRectBrush
	);

	D2D1_RECT_F titleRect = {
		0.f,
		0.f,
		PixelsToDIP(480.f * ratioX),
		PixelsToDIP(100.f * ratioY)
	};

	pGraphics->GetRenderTarget()->DrawTextW(
		L"rescan-act",
		10,
		pTitleTextFormat,
		titleRect,
		pTitleTextBrush
	);
}

void rescan::GameMenuScene::Update(double deltaTime)
{
}

void rescan::GameMenuScene::Begin()
{
	if (callback)
		callback->SceneHasBegun(this, NULL);
	tts->speak(L"Welcome! Please Use the up and down keys to choose a lesson.", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::GameMenuScene::End()
{
}

void rescan::GameMenuScene::Up()
{
	if (--selected >= lessonList.size())
		selected = lessonList.size() - 1;
}

void rescan::GameMenuScene::Down()
{
	if (++selected >= lessonList.size())
		selected = 0;
}

unsigned int rescan::GameMenuScene::GetSelected()
{
	return selected;
}

void rescan::GameMenuScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_UP:
		{
			Up();
			PlaySound(MAKEINTRESOURCE(IDR_WAVESELECT), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			tts->speak(lessonList[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			break;
		}
		case VK_DOWN:
			Down();
			PlaySound(MAKEINTRESOURCE(IDR_WAVESELECT), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			tts->speak(lessonList[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
			break;
		case VK_ESCAPE:
		{
			GameMenuSceneContext context;
			context.selectedLesson = selected;
			context.isExit = true;
			if (callback)
				callback->SceneHasEnded(this, &context);
		}
			break;
		case VK_RETURN:
		{
			GameMenuSceneContext context;
			context.selectedLesson = selected;
			context.isExit = false;
			if (callback)
				callback->SceneHasEnded(this, &context);
			break;
		}
		}
		
	}
}

std::wstring rescan::GameMenuScene::GetSelectedString()
{
	return lessonList[selected];
}
