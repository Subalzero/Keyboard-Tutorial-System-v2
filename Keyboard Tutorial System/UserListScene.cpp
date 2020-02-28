#include "stdafx.h"
#include "UserListScene.h"

rescan::UserListScene::UserListScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts, Keyboard* kbd, UserList* userList) :
	Scene(rect, gfx), tts(tts), kbd(kbd), userList(userList)
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
	RECT rect;
	GetClientRect(pGraphics->GetWindow(), &rect);
	D2D1_RECT_F textRect = {
		0.f,
		0.f,
		PixelsToDIP(rect.right),
		75.f
	};

	for (size_t i = 0; i < userList->users.size(); ++i)
	{
		if (i == selected)
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				userList->users[i].userName.c_str(),
				userList->users[i].userName.length(),
				pTextFormat,
				textRect,
				pSelectedTextBrush
			);
		}
		else
		{
			pGraphics->GetRenderTarget()->DrawTextW(
				userList->users[i].userName.c_str(),
				userList->users[i].userName.length(),
				pTextFormat,
				textRect,
				pTextBrush
			);
		}
		textRect.top += addHeight;
		textRect.bottom += addHeight;
	}

	if (selected == userList->users.size())
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
			if (selected == userList->users.size())
				call.willAddUser = true;
			else if (selected < userList->users.size())
				call.user = userList->users[selected];
			if (callback)
				callback->SceneHasEnded(this, &call);
			break;
		}
		}
	}
}

void rescan::UserListScene::Up()
{
	if (--selected > userList->users.size())
		selected = userList->users.size();
	if (selected == userList->users.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(userList->users[selected].userName.c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}

void rescan::UserListScene::Down()
{
	if (++selected > userList->users.size())
		selected = 0;
	if (selected == userList->users.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(userList->users[selected].userName.c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}

void rescan::UserListScene::Begin()
{
	selected = 0;
	if (selected == userList->users.size())
	{
		tts->speak(L"Add User", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
	else
	{
		tts->speak(userList->users[selected].userName.c_str(), TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
	}
}
