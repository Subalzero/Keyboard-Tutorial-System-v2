#pragma once

#include "Scene.h"
#include "TextToSpeech.h"
#include <list>

#define MAX_CHARACTERS 25

namespace rescan
{
	class NewUserScene : public Scene
	{
	public:
		NewUserScene(Rect rect, Graphics2D* gfx, Keyboard* kbd, TextToSpeech* tts);
		~NewUserScene();
		void Draw() override;
		void Update(double deltaTime) override;
		void KeyboardEvents(const Keyboard::Event& ev) override;
		void Begin() override;
	private:
		CComPtr<ID2D1SolidColorBrush> pWhiteBrush = nullptr;
		CComPtr<ID2D1SolidColorBrush> pBlackBrush = nullptr;

		CComPtr<IDWriteTextFormat> pTitleTextFormat = nullptr;
		CComPtr<IDWriteTextFormat> pTextFieldTextFormat = nullptr;

		bool drawCursor = false;
		std::list<wchar_t> textFieldChars;

		TextToSpeech* tts;
		Keyboard* kbd;
	};
}
