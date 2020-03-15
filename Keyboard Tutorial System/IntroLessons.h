#pragma once

#include "ILesson.h"
#include "TextToSpeech.h"

namespace rescan
{
	class Introduction1 : public ILesson
	{
	public:
		Introduction1(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);
		virtual ~Introduction1();
		virtual void Begin() override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;

		virtual void SpeakCurrentItem();
		virtual void LoadLessons();
	protected:
		virtual void SayHint();
	private:
		std::unique_ptr<TextToSpeech> tts;

		CComPtr<IDWriteTextFormat> pTextFormat;
		CComPtr<ID2D1SolidColorBrush> pWhiteBrush;

		Keyboard* kbd;
	};

	class Introduction2 : public ILesson
	{
	public:
		Introduction2(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);
		virtual ~Introduction2();
		virtual void Begin() override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;

		virtual void SpeakCurrentItem();
		virtual void LoadLessons();
	protected:
		virtual void SayHint();
	private:
		std::unique_ptr<TextToSpeech> tts;

		CComPtr<IDWriteTextFormat> pTextFormat;
		CComPtr<ID2D1SolidColorBrush> pWhiteBrush;

		Keyboard* kbd;
	};

	class Introduction3 : public ILesson
	{
	public:
		Introduction3(Rect rect, Graphics2D* gfx, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);
		virtual ~Introduction3();
		virtual void Begin() override;
		virtual void Draw() override;
		virtual void Update(double deltaTime) override;
		virtual void KeyboardEvents(const Keyboard::Event& ev) override;

		virtual void SpeakCurrentItem();
		virtual void LoadLessons();
	protected:
		virtual void SayHint();
	private:
		std::unique_ptr<TextToSpeech> tts;

		CComPtr<IDWriteTextFormat> pTextFormat;
		CComPtr<ID2D1SolidColorBrush> pWhiteBrush;

		Keyboard* kbd;
	};

	class Introduction4 : public ILesson
	{
	public:
		// Constructor.
		Introduction4(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();

	};

	class Introduction5 : public ILesson
	{
	public:
		// Constructor.
		Introduction5(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();

	};

	class Introduction6 : public ILesson
	{
	public:
		// Constructor.
		Introduction6(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);
		void KeyboardEvents(const Keyboard::Event& ev) override;
	private:
		void LoadLessons();
		void SpeakCurrentItem();

	};
}
