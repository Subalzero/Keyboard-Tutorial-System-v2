#include "stdafx.h"
#include "DashboardScene.h"
#include "Utils.h"

#define DB_LESSON 0
#define DB_PROGRESS 1

rescan::DashboardScene::DashboardScene(Rect rect, Graphics2D* gfx, Keyboard* kbd, TextToSpeech* tts) :
	Scene(rect, gfx), kbd(kbd), tts(tts)
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

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pBlueBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightBlue),
		&pLightBlueBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(0x4a5568),
		&pGray700Brush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(0x2d3748),
		&pGray800Brush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(0x1a202c),
		&pGray900Brush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(0xe2e8f0),
		&pLightGrayBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Roboto",
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

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Roboto",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		35.f,
		L"en-us",
		&pOptionTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTitleTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pOptionTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);

	sideOptions.push_back(L"LESSONS");
	sideOptions.push_back(L"PROGRESS");

	moduleNames.push_back(L"MODULE 1: INTRODUCTION");
	moduleNames.push_back(L"MODULE 2: LEFT HAND KEYS");
	moduleNames.push_back(L"MODULE 3: RIGHT HAND KEYS");
	moduleNames.push_back(L"MODULE 4: NUMBER KEYS AND NUMPAD");
	moduleNames.push_back(L"MODULE 5: PUNCTUATION MARK KEYS");

	module1Lessons.push_back(L"Introduction 1: Arrows and Enter");
	module1Lessons.push_back(L"Introduction 2: Control and Space");
	module1Lessons.push_back(L"Introduction 3: Escape");
	module1Lessons.push_back(L"Introduction 4: F and J Key");
	module1Lessons.push_back(L"Introduction 5: The Home Row");
	module1Lessons.push_back(L"Introduction 6: Shift Key");

	module2Lessons.push_back(L"Lesson 1: The Left Hand and Home Row Keys");
	module2Lessons.push_back(L"Lesson 2: The E Key");
	module2Lessons.push_back(L"Lesson 3: The R Key");
	module2Lessons.push_back(L"Lesson 4: The T Key");
	module2Lessons.push_back(L"Lesson 5: The W Key");
	module2Lessons.push_back(L"Lesson 6: The Q Key");
	module2Lessons.push_back(L"Lesson 7: The G Key");
	module2Lessons.push_back(L"Lesson 8: The C Key");
	module2Lessons.push_back(L"Lesson 9: The V Key");
	module2Lessons.push_back(L"Lesson 10: The X Key");
	module2Lessons.push_back(L"Lesson 11: The Z Key");
	module2Lessons.push_back(L"Lesson 12: The B Key");

	module3Lessons.push_back(L"Lesson 13: The Right Hand");
	module3Lessons.push_back(L"Lesson 14: The H Key");
	module3Lessons.push_back(L"Lesson 15: The I Key");
	module3Lessons.push_back(L"Lesson 16: The U Key");
	module3Lessons.push_back(L"Lesson 17: The O Key");
	module3Lessons.push_back(L"Lesson 18: The P Key");
	module3Lessons.push_back(L"Lesson 19: The Y Key");
	module3Lessons.push_back(L"Lesson 20: The N Key");
	module3Lessons.push_back(L"Lesson 21: The M Key");
	module3Lessons.push_back(L"Lesson 22: The Comma Key");
	module3Lessons.push_back(L"Lesson 23: The Period Key");

	module4Lessons.push_back(L"Lesson 24: Left Hand Number Row");
	module4Lessons.push_back(L"Lesson 25: Right Hand Number Row");
	module4Lessons.push_back(L"Lesson 26: The Entire Number Row");
	module4Lessons.push_back(L"Lesson 27: Numpad");

	module5Lessons.push_back(L"Lesson 28: Exclamation Mark and @ Symbol");
	module5Lessons.push_back(L"Lesson 29: Number and Dollar Sign");
	module5Lessons.push_back(L"Lesson 30: Percent and Caret");
	module5Lessons.push_back(L"Lesson 31: Ampersand and Asterisk");
	module5Lessons.push_back(L"Lesson 32: Left and Right Parenthesis");
	module5Lessons.push_back(L"Lesson 33: Underscore and Hyphen");
	module5Lessons.push_back(L"Lesson 34: Equal and Plus");
	module5Lessons.push_back(L"Lesson 35: Square Brackets");
	module5Lessons.push_back(L"Lesson 36: Curly Brackets");
	module5Lessons.push_back(L"Lesson 37: Less Than and Greater Than");
	module5Lessons.push_back(L"Lesson 38: Question Mark");
	module5Lessons.push_back(L"Lesson 39: Apostrophe");
	module5Lessons.push_back(L"Lesson 40: The Quotation Mark");
	module5Lessons.push_back(L"Lesson 41: The Colon Key");

	std::copy(module2Lessons.begin(), module2Lessons.end(), std::back_inserter(progressList));
	std::copy(module3Lessons.begin(), module3Lessons.end(), std::back_inserter(progressList));
	std::copy(module4Lessons.begin(), module4Lessons.end(), std::back_inserter(progressList));
	std::copy(module5Lessons.begin(), module5Lessons.end(), std::back_inserter(progressList));
}

rescan::DashboardScene::~DashboardScene()
{
}

void rescan::DashboardScene::Draw()
{
	RECT rect;
	GetClientRect(pGraphics->GetWindow(), &rect);
	D2D1_RECT_F titleRect = {
		0.0,
		0.0,
		PixelsToDIP(rect.right / 4.8),
		PixelsToDIP(rect.bottom / 10.8)
	};

	D2D1_RECT_F whiteBannerRect = {
		PixelsToDIP(rect.right / 4.8),
		0,
		PixelsToDIP(rect.right),
		PixelsToDIP(rect.bottom / 10.8)
	};

	D2D1_RECT_F sideMenuRect = {
		0.0,
		PixelsToDIP(rect.bottom / 10.8),
		PixelsToDIP(rect.right / 4.8),
		PixelsToDIP(rect.bottom)
	};

	D2D1_RECT_F centerMenuRect = {
		PixelsToDIP(rect.right / 4.8),
		PixelsToDIP(rect.bottom / 10.8),
		PixelsToDIP(rect.right),
		PixelsToDIP(rect.bottom)
	};

	D2D1_RECT_F sideOptionsMenuRect = {
		PixelsToDIP(15.f),
		PixelsToDIP(rect.bottom / 2.7),
		PixelsToDIP(rect.right / 4.8 - 15.f),
		PixelsToDIP(rect.bottom / 2.7) + 50.f
	};

	D2D1_RECT_F centerTitleRect = {
		centerMenuRect.left + PixelsToDIP(40.f),
		centerMenuRect.bottom / 8,
		centerMenuRect.right - PixelsToDIP(40.f),
		centerMenuRect.bottom / 8 + 50.f
	};

	pGraphics->GetRenderTarget()->FillRectangle(
		titleRect,
		pGray900Brush
	);

	pGraphics->GetRenderTarget()->FillRectangle(
		whiteBannerRect,
		pWhiteBrush
	);

	pGraphics->GetRenderTarget()->FillRectangle(
		sideMenuRect,
		pGray800Brush
	);

	pGraphics->GetRenderTarget()->FillRectangle(
		centerMenuRect,
		pLightGrayBrush
	);

	pGraphics->GetRenderTarget()->DrawTextW(
		L"Rescan",
		6,
		pTitleTextFormat,
		titleRect,
		pWhiteBrush
	);

	pGraphics->GetRenderTarget()->DrawLine(
		D2D1::Point2F(
			centerMenuRect.left + PixelsToDIP(40.f),
			centerMenuRect.bottom / 4
		),
		D2D1::Point2F(
			centerMenuRect.right - PixelsToDIP(40.f),
			centerMenuRect.bottom / 4
		),
		pGray700Brush
	);

	for (size_t i = 0; i < sideOptions.size(); ++i)
	{
		if (i == selectedSideOption)
		{
			pGraphics->GetRenderTarget()->FillRectangle(
				sideOptionsMenuRect,
				pLightBlueBrush
			);
		}

		pGraphics->GetRenderTarget()->DrawTextW(
			sideOptions[i].c_str(),
			sideOptions[i].length(),
			pOptionTextFormat,
			sideOptionsMenuRect,
			pWhiteBrush
		);

		sideOptionsMenuRect.top += 60;
		sideOptionsMenuRect.bottom += 60;
	}

	if (dashboardScreen == DB_LESSON)
	{
		if (moduleIsRendering)
		{
			pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			pGraphics->GetRenderTarget()->DrawTextW(
				L"DASHBOARD",
				9,
				pTitleTextFormat,
				centerTitleRect,
				pGray800Brush
			);
			pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

			D2D1_RECT_F optionsRect = {
				centerMenuRect.left + PixelsToDIP(40.f),
				centerMenuRect.bottom / 3,
				centerMenuRect.right - PixelsToDIP(40.f),
				centerMenuRect.bottom / 3 + 50.f
			};

			for (size_t i = 0; i < moduleNames.size(); ++i)
			{
				if (i == selectedModule)
				{
					pGraphics->GetRenderTarget()->FillRectangle(
						optionsRect,
						pBlueBrush
					);
				}
				pGraphics->GetRenderTarget()->DrawTextW(
					moduleNames[i].c_str(),
					moduleNames[i].length(),
					pOptionTextFormat,
					optionsRect,
					pGray700Brush
				);

				optionsRect.top += 50;
				optionsRect.bottom += 50;
			}
		}
		else
		{
			unsigned selected = 0;
			std::vector<std::wstring>* list = nullptr;

			CComPtr<ID2D1PathGeometry> pUpArrowPath;
			CComPtr<ID2D1PathGeometry> pDownArrowPath;

			pGraphics->GetD2DFactory()->CreatePathGeometry(&pUpArrowPath);
			pGraphics->GetD2DFactory()->CreatePathGeometry(&pDownArrowPath);

			// Up Arrow Shape
			ID2D1GeometrySink* pSink = nullptr;
			pUpArrowPath->Open(&pSink);
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
				pSink->BeginFigure(
					D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f,
						centerMenuRect.bottom / 4.f + PixelsToDIP(25.f)
					),
					D2D1_FIGURE_BEGIN_FILLED
				);
				D2D1_POINT_2F points[] = {
					D2D1::Point2F(
						(centerMenuRect.right + centerMenuRect.left) / 2.f - PixelsToDIP(15.f),
						centerMenuRect.bottom / 4.f + PixelsToDIP(50.f)
					),
					D2D1::Point2F(
						(centerMenuRect.right + centerMenuRect.left) / 2.f + PixelsToDIP(15.f),
						centerMenuRect.bottom / 4.f + PixelsToDIP(50.f)
					)
				};
				pSink->AddLines(points, ARRAYSIZE(points));
				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
				pSink->Close();
			}

			pSink->Release();
			pSink = nullptr;

			// Down Arrow Shape
			pDownArrowPath->Open(&pSink);
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
				pSink->BeginFigure(
					D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f,
						centerMenuRect.bottom - PixelsToDIP(25.f)
					),
					D2D1_FIGURE_BEGIN_FILLED
				);
				D2D1_POINT_2F points[] = {
					D2D1::Point2F(
						(centerMenuRect.right + centerMenuRect.left) / 2.f - PixelsToDIP(15.f),
						centerMenuRect.bottom - PixelsToDIP(50.f)
					),
					D2D1::Point2F(
						(centerMenuRect.right + centerMenuRect.left) / 2.f + PixelsToDIP(15.f),
						centerMenuRect.bottom - PixelsToDIP(50.f)
					)
				};
				pSink->AddLines(points, ARRAYSIZE(points));
				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
				pSink->Close();
			}

			pSink->Release();
			pSink = nullptr;

			pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			pGraphics->GetRenderTarget()->DrawTextW(
				L"Lessons",
				7,
				pTitleTextFormat,
				centerTitleRect,
				pGray800Brush
			);
			pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

			D2D1_RECT_F optionsRect = {
				centerMenuRect.left + PixelsToDIP(40.f),
				centerMenuRect.bottom / 3,
				centerMenuRect.right - PixelsToDIP(40.f),
				centerMenuRect.bottom / 3 + 50.f
			};

			switch (selectedModule)
			{
			case 0:
				selected = selectedLessonInMod1;
				list = &module1Lessons;
				break;
			case 1:
				selected = selectedLessonInMod2;
				list = &module2Lessons;
				break;
			case 2:
				selected = selectedLessonInMod3;
				list = &module3Lessons;
				break;
			case 3:
				selected = selectedLessonInMod4;
				list = &module4Lessons;
				break;
			case 4:
				selected = selectedLessonInMod5;
				list = &module5Lessons;
				break;
			}

			if (list)
			{
				unsigned j = (selected / 8) * 8;

				if (selected >= 8)
				{
					pGraphics->GetRenderTarget()->FillGeometry(
						pUpArrowPath,
						pBlackBrush
					);
				}


				if (((*list).size() - j) > 8)
				{
					pGraphics->GetRenderTarget()->FillGeometry(
						pDownArrowPath,
						pBlackBrush
					);
				}

				for (size_t i = 0; i < 8 && j < (*list).size(); ++i, ++j)
				{
					if (j == selected)
					{
						pGraphics->GetRenderTarget()->FillRectangle(
							optionsRect,
							pBlueBrush
						);
					}

					pGraphics->GetRenderTarget()->DrawTextW(
						(*list)[j].c_str(),
						(*list)[j].length(),
						pOptionTextFormat,
						optionsRect,
						pGray700Brush
					);

					optionsRect.top += 50;
					optionsRect.bottom += 50;
				}
			}


		}
	}
	else if (dashboardScreen == DB_PROGRESS)
	{
		pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		pGraphics->GetRenderTarget()->DrawTextW(
			L"Progress",
			8,
			pTitleTextFormat,
			centerTitleRect,
			pGray800Brush
		);
		pTitleTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		CComPtr<ID2D1PathGeometry> pUpArrowPath;
		CComPtr<ID2D1PathGeometry> pDownArrowPath;

		pGraphics->GetD2DFactory()->CreatePathGeometry(&pUpArrowPath);
		pGraphics->GetD2DFactory()->CreatePathGeometry(&pDownArrowPath);

		// Up Arrow Shape
		ID2D1GeometrySink* pSink = nullptr;
		pUpArrowPath->Open(&pSink);
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
			pSink->BeginFigure(
				D2D1::Point2F(
				(centerMenuRect.right + centerMenuRect.left) / 2.f,
					centerMenuRect.bottom / 4.f + PixelsToDIP(25.f)
				),
				D2D1_FIGURE_BEGIN_FILLED
			);
			D2D1_POINT_2F points[] = {
				D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f - PixelsToDIP(15.f),
					centerMenuRect.bottom / 4.f + PixelsToDIP(50.f)
				),
				D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f + PixelsToDIP(15.f),
					centerMenuRect.bottom / 4.f + PixelsToDIP(50.f)
				)
			};
			pSink->AddLines(points, ARRAYSIZE(points));
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
			pSink->Close();
		}

		pSink->Release();
		pSink = nullptr;

		// Down Arrow Shape
		pDownArrowPath->Open(&pSink);
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
			pSink->BeginFigure(
				D2D1::Point2F(
				(centerMenuRect.right + centerMenuRect.left) / 2.f,
					centerMenuRect.bottom - PixelsToDIP(25.f)
				),
				D2D1_FIGURE_BEGIN_FILLED
			);
			D2D1_POINT_2F points[] = {
				D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f - PixelsToDIP(15.f),
					centerMenuRect.bottom - PixelsToDIP(50.f)
				),
				D2D1::Point2F(
					(centerMenuRect.right + centerMenuRect.left) / 2.f + PixelsToDIP(15.f),
					centerMenuRect.bottom - PixelsToDIP(50.f)
				)
			};
			pSink->AddLines(points, ARRAYSIZE(points));
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
			pSink->Close();
		}

		pSink->Release();
		pSink = nullptr;

		unsigned j = (selectedProgressItem / 8) * 8;

		if (selectedProgressItem >= 8)
		{
			pGraphics->GetRenderTarget()->FillGeometry(
				pUpArrowPath,
				pBlackBrush
			);
		}

		if ((progressList.size() - j) > 8)
		{
			pGraphics->GetRenderTarget()->FillGeometry(
				pDownArrowPath,
				pBlackBrush
			);
		}

		D2D1_RECT_F optionsRect = {
			centerMenuRect.left + PixelsToDIP(40.f),
			centerMenuRect.bottom / 3,
			centerMenuRect.right - PixelsToDIP(40.f),
			centerMenuRect.bottom / 3 + 50.f
		};

		for (size_t i = 0; i < 8 && j < progressList.size(); ++i, ++j)
		{
			if (j == selectedProgressItem)
			{
				pGraphics->GetRenderTarget()->FillRectangle(
					optionsRect,
					pBlueBrush
				);
			}

			pGraphics->GetRenderTarget()->DrawTextW(
				progressList[j].c_str(),
				progressList[j].length(),
				pOptionTextFormat,
				optionsRect,
				pGray700Brush
			);

			optionsRect.top += 50;
			optionsRect.bottom += 50;
		}
	}
}

void rescan::DashboardScene::Update(double deltaTime)
{
}

void rescan::DashboardScene::Begin()
{
	moduleIsRendering = true;
	dashboardScreen = DB_LESSON;
	selectedSideOption = 0;
	selectedModule = 0;
	selectedLessonInMod1 = 0;
	selectedLessonInMod2 = 0;
	selectedLessonInMod3 = 0;
	selectedLessonInMod4 = 0;
	selectedLessonInMod5 = 0;
	selectedProgressItem = 0;
}

void rescan::DashboardScene::Up()
{
	std::wstringstream wss;
	if (dashboardScreen == DB_LESSON)
	{
		if (moduleIsRendering)
		{
			if (selectedModule - 1 < moduleNames.size())
			{
				--selectedModule;
				wss << moduleNames[selectedModule];
			}
		}
		else
		{
			switch (selectedModule)
			{
			case 0:
				if (selectedLessonInMod1 - 1 >= 0)
				{
					--selectedLessonInMod1;
					wss << module1Lessons[selectedLessonInMod1];
				}
				break;
			case 1:
				if (selectedLessonInMod2 - 1 < module2Lessons.size())
				{
					--selectedLessonInMod2;
					wss << module2Lessons[selectedLessonInMod2];
				}
				break;
			case 2:
				if (selectedLessonInMod3 - 1 < module3Lessons.size())
				{
					--selectedLessonInMod3;
					wss << module3Lessons[selectedLessonInMod3];
				}
				break;
			case 3:
				if (selectedLessonInMod4 - 1 < module4Lessons.size())
				{
					--selectedLessonInMod4;
					wss << module4Lessons[selectedLessonInMod4];
				}
				break;
			case 4:
				if (selectedLessonInMod5 - 1 < module5Lessons.size())
				{
					--selectedLessonInMod5;
					wss << module5Lessons[selectedLessonInMod5];
				}
				break;
			}
		}
	}
	else if (dashboardScreen == DB_PROGRESS)
	{
		if (selectedProgressItem - 1 < progressList.size())
		{
			--selectedProgressItem;
			wss << progressList[selectedProgressItem];
		}
	}
	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::DashboardScene::Down()
{
	std::wstringstream wss;
	if (dashboardScreen == DB_LESSON)
	{
		if (moduleIsRendering)
		{
			if (selectedModule + 1ul < moduleNames.size())
			{
				++selectedModule;
				wss << moduleNames[selectedModule];
			}
		}
		else
		{
			switch (selectedModule)
			{
			case 0:
				if (selectedLessonInMod1 + 1 < module1Lessons.size())
				{
					++selectedLessonInMod1;
					wss << module1Lessons[selectedLessonInMod1];
				}
				break;
			case 1:
				if (selectedLessonInMod2 + 1 < module2Lessons.size())
					wss << module2Lessons[++selectedLessonInMod2];
				break;
			case 2:
				if (selectedLessonInMod3 + 1 < module3Lessons.size())
					wss << module3Lessons[++selectedLessonInMod3];
				break;
			case 3:
				if (selectedLessonInMod4 + 1 < module4Lessons.size())
					wss << module4Lessons[++selectedLessonInMod4];
				break;
			case 4:
				if (selectedLessonInMod5 + 1 < module5Lessons.size())
					wss << module5Lessons[++selectedLessonInMod5];
				break;
			}
		}
	}
	else if (dashboardScreen == DB_PROGRESS)
	{
		if (selectedProgressItem + 1 < progressList.size())
			wss << progressList[++selectedProgressItem];
	}
	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::DashboardScene::Tab()
{
	std::wstringstream wss;
	if (++selectedSideOption >= sideOptions.size())
	{
		selectedSideOption = 0;
	}
	dashboardScreen = selectedSideOption;
	wss << sideOptions[selectedSideOption];
	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

void rescan::DashboardScene::SetUser(User user)
{
	this->user = user;
}

rescan::User& rescan::DashboardScene::GetUser()
{
	return user;
}

unsigned rescan::DashboardScene::GetSelected()
{
	return 0;
}

void rescan::DashboardScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_TAB:
		{
			Tab();
			return;
		}
		case VK_UP:
		{
			Up();
			return;
		}
		case VK_DOWN:
		{
			Down();
			return;
		}
		case VK_RETURN:
		{
			if (dashboardScreen == DB_LESSON)
			{
				if (moduleIsRendering)
				{
					moduleIsRendering = !moduleIsRendering;
					unsigned selected = 0;
					std::vector<std::wstring>* list = nullptr;
					switch (selectedModule)
					{
					case 0:
						list = &module1Lessons;
						selected = selectedLessonInMod1;
						break;
					case 1:
						list = &module2Lessons;
						selected = selectedLessonInMod2;
						break;
					case 2:
						list = &module3Lessons;
						selected = selectedLessonInMod3;
						break;
					case 3:
						list = &module4Lessons;
						selected = selectedLessonInMod4;
						break;
					case 4:
						list = &module5Lessons;
						selected = selectedLessonInMod5;
						break;
					}
					tts->speak((*list)[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
				}
				else if (!moduleIsRendering)
				{
					DashboardSceneContext cont = { 0 };
					cont.selectedModule = selectedModule;
					switch (selectedModule)
					{
					case 0:
						cont.selectedLesson = -selectedLessonInMod1;
						break;
					case 1:
						cont.selectedLesson = selectedLessonInMod2;
						break;
					case 2:
						cont.selectedLesson = selectedLessonInMod3 + 12;
						break;
					case 3:
						cont.selectedLesson = selectedLessonInMod4 + 23;
						break;
					case 4:
						cont.selectedLesson = selectedLessonInMod5 + 27;
						break;
					}
					cont.user = user;
					if (callback)
						callback->SceneHasEnded(this, &cont);
				}
			}
			return;
		}
		case VK_ESCAPE:
		{
			if (dashboardScreen == DB_LESSON)
			{
				if (!moduleIsRendering)
				{
					moduleIsRendering = !moduleIsRendering;
					tts->speak(moduleNames[selectedModule].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
					return;
				}
			}
			DashboardSceneContext cont = { 0 };
			cont.isExit = true;
			if (callback)
				callback->SceneHasEnded(this, &cont);
			return;
		}
		case VK_DELETE:
		{
			DashboardSceneContext cont = { 0 };
			cont.willDeleteUser = true;
			cont.user = user;
			if (callback)
				callback->SceneHasEnded(this, &cont);
		}
		}
	}
}

std::wstring rescan::DashboardScene::GetSelectedString()
{
	return std::wstring();
}
