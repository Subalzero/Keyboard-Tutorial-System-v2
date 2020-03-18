#pragma once

#include "Scene.h"
#include "TextToSpeech.h"
#include "UserList.h"

namespace rescan
{
	class UserListScene : public Scene
	{
	public:
		struct UserListSceneContext
		{
			unsigned selected;
			bool willAddUser;
			bool isExit;
			User* user;
		};
		UserListScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts, Keyboard* kbd, UserList* userList);
		virtual ~UserListScene();
		void Draw() override;
		void Update(double deltaTime) override;
		void KeyboardEvents(const Keyboard::Event& ev) override;
		void Up();
		void Down();
		void Begin() override;
	private:
		TextToSpeech* tts;
		Keyboard* kbd;

		CComPtr<ID2D1SolidColorBrush> pTextBrush = nullptr;
		CComPtr<ID2D1SolidColorBrush> pSelectedTextBrush = nullptr;
		CComPtr<IDWriteTextFormat> pTextFormat = nullptr;

		std::vector<std::wstring> options;

		unsigned int selected = 0;

		UserList* userList;
	};
}

