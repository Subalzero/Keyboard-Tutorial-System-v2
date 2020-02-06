#pragma once

#include "stdafx.h"
#include "ILesson.h"
#include "Utils.h"

namespace rescan
{
	class Lesson41 :
		public ILesson
	{
	public:
		Lesson41(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson42 :
		public ILesson
	{
	public:
		Lesson42(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson43 :
		public ILesson
	{
	public:
		Lesson43(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};
}