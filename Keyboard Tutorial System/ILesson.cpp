#include "stdafx.h"
#include "ILesson.h"

rescan::ILesson::ILesson(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts, int lesson) :
	Scene(rect, graphics),
	keyboard(kbd),
	mouse(mouse),
	errors(0),
	index(0),
	numOfCorrectItems(0),
	pCharBrush(nullptr),
	pHighlightedCharBrush(nullptr),
	pTextFormat(nullptr),
	totalChars(0),
	fontSize(300.f),
	tts(tts),
	lesson(lesson),
	done(false),
	totalTime(0.f),
	isPaused(false)
{
	HRESULT hr;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pCharBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pHighlightedCharBrush
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
		fontSize * ratio,
		L"en_us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

}

rescan::ILesson::~ILesson()
{
	if (pCharBrush)
	{
		pCharBrush->Release();
		pCharBrush = nullptr;
	}

	if (pHighlightedCharBrush)
	{
		pHighlightedCharBrush->Release();
		pHighlightedCharBrush = nullptr;
	}

	if (pTextFormat)
	{
		pTextFormat->Release();
		pTextFormat = nullptr;
	}
}

void rescan::ILesson::Begin()
{
	errors = 0;
	index = 0;
	numOfCorrectItems = 0;
	totalChars = 0;
	fontSize = 300.f;
	totalTime = 0.f;
	isPaused = false;
	done = false;
	LoadLessons();
	for (size_t i = 0; i < itemList.size(); ++i)
	{
		totalChars += itemList[i].length();
	}
	keyboard->FlushChar();
	SpeakCurrentItem();
}

void rescan::ILesson::End()
{
}

void rescan::ILesson::Draw()
{
	RECT rc;
	GetClientRect(pGraphics->GetWindow(), &rc);
	float ratio = (float(rc.bottom) - float(rc.top)) / 1080;
	D2D1_RECT_F rect = {
		30.f,
		(rc.bottom - fontSize) * 0.5f,
		80.f,
		(rc.bottom + fontSize) * 0.5f
	};
	float j = 60;
	for (unsigned int i = 0; i < itemList[index].length(); ++i)
	{
		CComPtr<IDWriteTextLayout> textLayout;
		rect.left = j + 0.f;
		rect.right = j + (fontSize * 0.6666f);
		std::wstring wstr(1, itemList[index][i]);
		HRESULT hr = pGraphics->GetDWriteFactory()->CreateTextLayout(
			wstr.c_str(),
			1,
			pTextFormat,
			fontSize * 0.6666f,
			fontSize * ratio,
			&textLayout
		);
		if (SUCCEEDED(hr))
		{
			DWRITE_TEXT_METRICS metrics;
			textLayout->GetMetrics(&metrics);
			float width = metrics.widthIncludingTrailingWhitespace;
			if (i < numOfCorrectItems)
			{
				pGraphics->GetRenderTarget()->DrawTextLayout(
					D2D1::Point2F(rect.left, rect.top),
					textLayout,
					pHighlightedCharBrush
				);
			}
			else
			{
				pGraphics->GetRenderTarget()->DrawTextLayout(
					D2D1::Point2F(rect.left, rect.top),
					textLayout,
					pCharBrush
				);
			}
			j += width;
		}
	}
}

void rescan::ILesson::Update(double deltaTime)
{
	if (index >= itemList.size())
		index = itemList.size() - 1;
	if (lesson == -4 && index == 0 && IsCurrentItemComplete() && !done)
	{
		tts->speak(L"Now press the space key to continue.", TTSFLAGS_ASYNC);
		done = true;
	}
	if (!isPaused)
	{
		totalTime += deltaTime;
	}
}

void rescan::ILesson::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_CONTROL:
		{
			SayHint();
			return;
		}
		case VK_ESCAPE:
		{
			LessonContext cont;
			cont.errors = this->errors;
			cont.index = index;
			cont.lesson = lesson;
			cont.numOfCorrectItems = numOfCorrectItems;
			cont.totalChars = totalChars;
			cont.isExit = true;
			Pause();
			if (callback)
				callback->SceneHasEnded(this, &cont);
			return;
		}
		}

		while (const auto ch = keyboard->ReadChar())
		{
			if (IsCurrentItemComplete())
			{
				if (*ch == ' ')
				{
					PlaySound(
						MAKEINTRESOURCE(IDR_WAVECHECK),
						GetModuleHandle(NULL),
						SND_RESOURCE | SND_ASYNC
					);
					++index;
					if (index < itemList.size())
					{
						numOfCorrectItems = 0;
						SpeakCurrentItem();
					}
					else
					{
						PlaySound(
							MAKEINTRESOURCE(IDR_WAVECOMPLETE),
							GetModuleHandle(NULL),
							SND_RESOURCE | SND_ASYNC
						);
						int count = 0;
						for (std::wstring wstr : itemList)
						{
							count += CountWords(wstr);
						}

						LessonContext cont = { 0 };
						cont.errors = errors;
						cont.index = index;
						cont.lesson = lesson;
						cont.numOfCorrectItems = numOfCorrectItems;
						cont.totalChars = totalChars;
						cont.isExit = false;
						cont.totalTime = totalTime;
						cont.wordsPerMinute = count / (totalTime / 60.f);

						if (callback)
							callback->SceneHasEnded(this, &cont);
					}
				}
				else
				{
					tts->speak(L"Please press the space key to continue.", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
				}
				return;
			}
			else if (*ch == itemList[index][numOfCorrectItems])
			{
				++numOfCorrectItems;
			}
			else
			{
				PlaySound(
					MAKEINTRESOURCE(IDR_WAVEWRONG),
					GetModuleHandle(NULL),
					SND_RESOURCE | SND_ASYNC
				);
				++errors;
			}
			SpeakChar(*ch);
		}
		
		if (ev.GetCode() == VK_CAPITAL)
		{
			std::wstringstream wss;
			wss << L"Caps Lock toggle ";
			short state = GetKeyState(VK_CAPITAL);
			wss << (state & 1) ? L"on" : L"off";
			tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
		}
	}
}

void rescan::ILesson::MouseEvents(const Mouse::Event& ev)
{
	if (ev.GetType() == Mouse::Event::Type::WheelUp)
	{
		if (fontSize < 300)
			fontSize += 10;
		SetFontSize(fontSize);
	}
	else if (ev.GetType() == Mouse::Event::Type::WheelDown)
	{
		if (fontSize > 100)
			fontSize -= 10;
		SetFontSize(fontSize);
	}
}

bool rescan::ILesson::IsCurrentItemComplete()
{
	return numOfCorrectItems == itemList[index].length();
}

void rescan::ILesson::Pause()
{
	isPaused = true;
}

void rescan::ILesson::Resume()
{
	isPaused = false;
	keyboard->FlushChar();
}

void rescan::ILesson::SayHint()
{
	std::wstringstream wss;
	for (unsigned int i = numOfCorrectItems; i < itemList[index].length(); ++i)
	{
		if (iswalpha(itemList[index][i]) && iswupper(itemList[index][i]))
		{
			wss << L" Capital ";
			wss << itemList[index][i];
			continue;
		}
		else if (iswalpha(itemList[index][i]))
		{
			wss << L" " << itemList[index][i] << L" ";
			continue;
		}
		else if (itemList[index][i] == ' ')
		{
			wss << L" space";
		}
		else if (itemList[index][i] == '<')
		{
			wss << L" lesser than sign";
			continue;
		}
		else if (itemList[index][i] == '>')
		{
			wss << L" greater than sign";
			continue;
		}
		else if (itemList[index][i] == '.')
		{
			wss << L" period";
			continue;
		}
		else  if (itemList[index][i] == '?')
		{
			wss << L" question mark";
			continue;
		}
		else if (itemList[index][i] == '!')
		{
			wss << L" exclamation point";
			continue;
		}
		else
		{
			wss << L" <spell> ";
			wss << itemList[index][i];
			wss << L" </spell> ";
		}
	}
	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK | TTSFLAGS_IS_XML);
}

void rescan::ILesson::SetFontSize(float size)
{
	if (pTextFormat)
	{
		pTextFormat->Release();
		pTextFormat = nullptr;
	}

	fontSize = size;

	HRESULT hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void rescan::ILesson::SpeakChar(char ch)
{
	std::wstringstream wss;
	if (iswupper(ch) && iswalpha(ch))
	{
		wss << L"Cap " << ch;
	}
	else if (ch == ' ')
	{
		wss << L"Space";
	}
	else if (ch == '<')
	{
		wss << L"Lesser than sign";
	}
	else
	{
		wss << L"<spell>"
			<< ch
			<< L"</spell>";
	}

	tts->speak(wss.str().c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
}

int rescan::ILesson::CountWords(const std::wstring& ws)
{
	int count = 0;
	if (ws.empty())
		return 0;
	std::wstringstream wss(ws);
	do
	{
		std::wstring temp;
		wss >> temp;
		if (temp.empty())
			continue;
		++count;
	} while (wss);
	return count;
}
