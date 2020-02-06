#pragma once

#include "Scene.h"
#include "TextToSpeech.h"

namespace rescan
{
	class ScoreScene : public Scene
	{
	public:
		ScoreScene(Rect rect, Graphics2D* gfx, TextToSpeech* tts);
		virtual ~ScoreScene();
		virtual void Begin() override;
		virtual void End() override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		void SetScore(double time, double wpm, double accuracy);
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;
	public:
		SceneCallback* callback;
	private:
		CComPtr<ID2D1SolidColorBrush> pTextBrush;
		CComPtr<IDWriteTextFormat> pTextFormat;
		CComPtr<IDWriteTextFormat> pBigTextFormat;
		CComPtr<ID2D1SolidColorBrush> pRectBrush;

		double rectHeight;
		double opacity;

		std::wstring timeWStr;
		std::wstring WPMWStr;
		std::wstring accuracyWStr;

		double time;
		double WPM;
		double accuracy;

		TextToSpeech* tts;
	};
}
