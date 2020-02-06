#pragma once

#include "stdafx.h"
#include "ILesson.h"
#include "Utils.h"

namespace rescan
{
	class Lesson1 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson1(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();

	};

	class Lesson2 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson2(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson3 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson3(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson4 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson4(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson5 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson5(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson6 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson6(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson7 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson7(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson8 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson8(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson9 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson9(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();
	};

	class Lesson10 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson10(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void LoadLessons();
		void SpeakCurrentItem();

	};
}

