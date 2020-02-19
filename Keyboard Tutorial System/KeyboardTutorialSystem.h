#pragma once

#include "Application.h"
#include "TextToSpeech.h"
#include "Scene.h"
#include "GameMenuScene.h"
#include "Lessons.h"
#include "Lessons2.h"
#include "Lessons3.h"
#include "Lessons4.h"
#include "Lessons5.h"
#include "ScoreScene.h"
#include "QuitMessageScene.h"
#include "MainMenuScene.h"
#include "UserListScene.h"

#define LESSON(i) lesson##i

namespace rescan
{
	class KeyboardTutorialSystem : public Application, public SceneCallback
	{
	public:
		KeyboardTutorialSystem(const std::wstring& commandLine = L"");
		~KeyboardTutorialSystem();

		void SetFocusedScene(Scene* scene);
		void DoFrame() override;

		void SceneHasBegun(Scene* scene, void* context) override;
		void SceneHasEnded(Scene* scene, void* context) override;
	private:
		TextToSpeech* tts;
		Scene* focusedScene;
		GameMenuScene* menuScene;

		Lesson1* lesson1;
		Lesson2* lesson2;
		Lesson3* lesson3;
		Lesson4* lesson4;
		Lesson5* lesson5;
		Lesson6* lesson6;
		Lesson7* lesson7;
		Lesson8* lesson8;
		Lesson9* lesson9;
		Lesson10* lesson10;
		Lesson11* lesson11;
		Lesson12* lesson12;
		Lesson13* lesson13;
		Lesson14* lesson14;
		Lesson15* lesson15;
		Lesson16* lesson16;
		Lesson17* lesson17;
		Lesson18* lesson18;
		Lesson19* lesson19;
		Lesson20* lesson20;
		Lesson21* lesson21;
		Lesson22* lesson22;
		Lesson23* lesson23;
		Lesson24* lesson24;
		Lesson25* lesson25;
		Lesson26* lesson26;
		Lesson27* lesson27;
		Lesson28* lesson28;
		Lesson29* lesson29;
		Lesson30* lesson30;
		Lesson31* lesson31;
		Lesson32* lesson32;
		Lesson33* lesson33;
		Lesson34* lesson34;
		Lesson35* lesson35;
		Lesson36* lesson36;
		Lesson37* lesson37;
		Lesson38* lesson38;
		Lesson39* lesson39;
		Lesson40* lesson40;
		Lesson41* lesson41;
		Lesson42* lesson42;
		Lesson43* lesson43;

		std::unique_ptr<ScoreScene> scoreScene;

		std::unique_ptr<QuitMessageScene> quitScene;

		std::unique_ptr<MainMenuScene> mainMenuScene;

		std::unique_ptr<UserListScene> userListScene;

		std::vector<ILesson*> lessonList;

		std::vector<Scene*> scenes;
	};
}

