#pragma once

#include "Scene.h"
#include "TextToSpeech.h"

namespace rescan
{
	class MainMenuScene : public Scene
	{
	public:
		struct MainMenuSceneContext
		{
			int index;
			bool isExit;
		};

		MainMenuScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts, Keyboard* kbd);
		virtual ~MainMenuScene();
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
		virtual void Begin() override;
		void Up();
		void Down();
	private:
		TextToSpeech* tts;
		Keyboard* kbd;
		std::vector<std::wstring> options;
		CComPtr<ID2D1SolidColorBrush> pTitleBrush = nullptr;
		CComPtr<ID2D1SolidColorBrush> pUpperRectBrush = nullptr;
		CComPtr<IDWriteTextFormat> pTitleFormat = nullptr;
		CComPtr<ID2D1SolidColorBrush> pTextBrush = nullptr;
		CComPtr<ID2D1SolidColorBrush> pSelectedTextBrush = nullptr;
		CComPtr<IDWriteTextFormat> pTextFormat = nullptr;
		CComPtr<ID2D1SolidColorBrush> pCenterRectBrush = nullptr;

		unsigned int index;
	};
}
