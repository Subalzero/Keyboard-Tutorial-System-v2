#pragma once

#include "Scene.h"
#include "Graphics2D.h"
#include "Keyboard.h"
#include "TextToSpeech.h"

namespace rescan
{
	class GameMenuScene : public Scene
	{
	public:
		struct GameMenuSceneContext
		{
			bool isExit;
			unsigned int selectedLesson;
		};
		GameMenuScene(Rect frame, Graphics2D* graphics, Keyboard* kbd, TextToSpeech* tts);
		~GameMenuScene();
		void Draw() override;
		void Update(double deltaTime) override;
		void Begin() override;
		void End() override;
		void Up();
		void Down();
		unsigned int GetSelected();
		void KeyboardEvents(const Keyboard::Event& ev) override;
		std::wstring GetSelectedString();
	public:

	private:
		ID2D1SolidColorBrush* pTextBrush;
		ID2D1SolidColorBrush* pSelectedTextBrush;
		ID2D1SolidColorBrush* pMenuRectBrush;
		ID2D1SolidColorBrush* pSideRectBrush;
		ID2D1SolidColorBrush* pUpperRectBrush;
		ID2D1SolidColorBrush* pTitleTextBrush;
		IDWriteTextFormat* pTextFormat;
		IDWriteTextFormat* pTitleTextFormat;
		ID2D1SolidColorBrush* pArrowBrush;
		ID2D1SolidColorBrush* pSelectedArrowBrush;
		ID2D1PathGeometry* pUpArrowPath;
		ID2D1PathGeometry* pDownArrowPath;

		Keyboard* keyboard;
		TextToSpeech* tts;

		std::vector<std::wstring> lessonList;
		unsigned int selected;
	};
}

