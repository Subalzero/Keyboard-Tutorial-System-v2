#include "stdafx.h"
#include "UserListScene.h"

rescan::UserListScene::UserListScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts, Keyboard* kbd) :
	Scene(rect, gfx), tts(tts), kbd(kbd)
{
	HRESULT hr;

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&pTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pSelectedTextBrush
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	hr = pGraphics->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		75.f,
		L"en-us",
		&pTextFormat
	);

	if (FAILED(hr))
		throw WND_EXCEPT(hr);

	pTextFormat->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

rescan::UserListScene::~UserListScene()
{
}

void rescan::UserListScene::Draw()
{
	float addHeight = 75.f;
	D2D1_RECT_F textRect = {
		0.f,
		0.f,
		400.f,
		75.f
	};

	for (size_t i = 0; i < options.size(); ++i)
	{
		if (i == selected)
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				options[i].c_str(),
				options[i].length(),
				pTextFormat,
				textRect,
				pSelectedTextBrush
			);
		}
		else
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				options[i].c_str(),
				options[i].length(),
				pTextFormat,
				textRect,
				pTextBrush
			);
		}
		textRect.top += addHeight;
		textRect.bottom += addHeight;
	}

	if (selected == options.size())
	{
		pGraphics->GetRenderTarget()->DrawTextW(
			L"Add user",
			8,
			pTextFormat,
			textRect,
			pSelectedTextBrush
		);
	}
	else
	{
		pGraphics->GetRenderTarget()->DrawTextW(
			L"Add user",
			8,
			pTextFormat,
			textRect,
			pTextBrush
		);
	}
}

void rescan::UserListScene::Update(double deltaTime)
{
}

void rescan::UserListScene::KeyboardEvents(const Keyboard::Event& ev)
{
	if (ev.IsPress())
	{
		switch (ev.GetCode())
		{
		case VK_UP:
			Up();
			break;
		case VK_DOWN:
			Down();
			break;
		case VK_ESCAPE:
		{
			UserListSceneContext call = { 0 };
			call.isExit = true;
			if (callback)
				callback->SceneHasEnded(this, &call);
			break;
		}
		case VK_RETURN:
		{
			UserListSceneContext call = { 0 };
			call.selected = selected;
			if (selected == options.size())
				call.willAddUser = true;
			if (callback)
				callback->SceneHasEnded(this, &call);
			break;
		}
		}
	}
}

void rescan::UserListScene::Up()
{
	if (--selected > options.size())
		selected = options.size();
	if (selected == options.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(options[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}

void rescan::UserListScene::Down()
{
	if (++selected > options.size())
		selected = 0;
	if (selected == options.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(options[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}

void rescan::UserListScene::Begin()
{
	selected = 0;
	if (selected == options.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(options[selected].c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}
