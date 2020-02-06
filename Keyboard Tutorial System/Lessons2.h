#pragma once

#include "stdafx.h"
#include "ILesson.h"
#include "Utils.h"

namespace rescan
{
	class Lesson11 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson11(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson12 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson12(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson13 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson13(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson14 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson14(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson15 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson15(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson16 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson16(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson17 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson17(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson18 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson18(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson19 :
		public ILesson
	{
	public:
		Lesson19(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};

	class Lesson20 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson20(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();
	};
}
