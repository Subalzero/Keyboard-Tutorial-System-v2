#pragma once

#include "stdafx.h"
#include "ILesson.h"
#include "Utils.h"

namespace rescan
{
	class Lesson21 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson21(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson22 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson22(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson23 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson23(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson24 :
		public ILesson
	{
	public:
		// Constructor.
		Lesson24(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson25 :
		public ILesson
	{
	public:
		Lesson25(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson26 :
		public ILesson
	{
	public:
		Lesson26(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson27 :
		public ILesson
	{
	public:
		Lesson27(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson28 :
		public ILesson
	{
	public:
		Lesson28(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson29 :
		public ILesson
	{
	public:
		Lesson29(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};

	class Lesson30 :
		public ILesson
	{
	public:
		Lesson30(Rect rect, Graphics2D* graphics, Keyboard* kbd, Mouse* mouse, TextToSpeech* tts);

	private:
		void SpeakCurrentItem();
		void LoadLessons();

	};
}