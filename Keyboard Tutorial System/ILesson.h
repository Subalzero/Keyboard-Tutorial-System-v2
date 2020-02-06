#pragma once

#include "Scene.h"
#include "TextToSpeech.h"

namespace rescan
{
	class ILesson : public Scene
	{
	public:
		struct LessonContext
		{
			int lesson;
			unsigned int index;
			unsigned int numOfCorrectItems;
			unsigned totalChars;
			unsigned errors;
			double totalTime;
			double wordsPerMinute;
			bool isPaused;
			bool isExit;
		};

		ILesson(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts, int lesson);
		virtual ~ILesson();
		virtual void Begin() override;
		virtual void End() override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
		virtual void MouseEvents(const Mouse::Event& ev) override;
		virtual bool IsCurrentItemComplete();
		void Pause();
		void Resume();

		virtual void SpeakCurrentItem() = 0;
		virtual void LoadLessons() = 0;
	protected:
		virtual void SayHint();
		virtual void SetFontSize(float size);
		virtual void SpeakChar(char ch);
		int CountWords(const std::wstring& ws);
	protected:
		Keyboard* keyboard;
		Mouse* mouse;

		std::vector<std::wstring> itemList;
		std::wifstream filestream;
		
		unsigned int index;
		unsigned int numOfCorrectItems;
		unsigned totalChars;
		unsigned errors;

		ID2D1SolidColorBrush* pCharBrush;
		ID2D1SolidColorBrush* pHighlightedCharBrush;
		IDWriteTextFormat* pTextFormat;

		float fontSize;
		TextToSpeech* tts;
		int lesson;

		bool done;
		bool isPaused;

		double totalTime;
	};
}

