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
#include "NewUserScene.h"
#include "UserList.h"
#include "DeleteUserScene.h"
#include "DashboardScene.h"
#include "IntroLessons.h"

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

		std::unique_ptr<Lesson1> lesson1;
		std::unique_ptr<Lesson2> lesson2;
		std::unique_ptr<Lesson3> lesson3;
		std::unique_ptr<Lesson4> lesson4;
		std::unique_ptr<Lesson5> lesson5;
		std::unique_ptr<Lesson6> lesson6;
		std::unique_ptr<Lesson7> lesson7;
		std::unique_ptr<Lesson8> lesson8;
		std::unique_ptr<Lesson9> lesson9;
		std::unique_ptr<Lesson10> lesson10;
		std::unique_ptr<Lesson11> lesson11;
		std::unique_ptr<Lesson12> lesson12;
		std::unique_ptr<Lesson13> lesson13;
		std::unique_ptr<Lesson14> lesson14;
		std::unique_ptr<Lesson15> lesson15;
		std::unique_ptr<Lesson16> lesson16;
		std::unique_ptr<Lesson17> lesson17;
		std::unique_ptr<Lesson18> lesson18;
		std::unique_ptr<Lesson19> lesson19;
		std::unique_ptr<Lesson20> lesson20;
		std::unique_ptr<Lesson21> lesson21;
		std::unique_ptr<Lesson22> lesson22;
		std::unique_ptr<Lesson23> lesson23;
		std::unique_ptr<Lesson24> lesson24;
		std::unique_ptr<Lesson25> lesson25;
		std::unique_ptr<Lesson26> lesson26;
		std::unique_ptr<Lesson27> lesson27;
		std::unique_ptr<Lesson28> lesson28;
		std::unique_ptr<Lesson29> lesson29;
		std::unique_ptr<Lesson30> lesson30;
		std::unique_ptr<Lesson31> lesson31;
		std::unique_ptr<Lesson32> lesson32;
		std::unique_ptr<Lesson33> lesson33;
		std::unique_ptr<Lesson34> lesson34;
		std::unique_ptr<Lesson35> lesson35;
		std::unique_ptr<Lesson36> lesson36;
		std::unique_ptr<Lesson37> lesson37;
		std::unique_ptr<Lesson38> lesson38;
		std::unique_ptr<Lesson39> lesson39;
		std::unique_ptr<Lesson40> lesson40;
		std::unique_ptr<Lesson41> lesson41;

		std::unique_ptr<ScoreScene> scoreScene;
		std::unique_ptr<QuitMessageScene> quitScene;
		std::unique_ptr<MainMenuScene> mainMenuScene;
		std::unique_ptr<UserListScene> userListScene;
		std::unique_ptr<NewUserScene> newUserScene;
		std::unique_ptr<DeleteUserScene> deleteUserScene;
		std::unique_ptr<DashboardScene> dashboardScene;

		std::unique_ptr<Introduction1> introLesson1;
		std::unique_ptr<Introduction2> introLesson2;
		std::unique_ptr<Introduction3> introLesson3;
		std::unique_ptr<Introduction4> introLesson4;
		std::unique_ptr<Introduction5> introLesson5;
		std::unique_ptr<Introduction6> introLesson6;

		std::vector<ILesson*> lessonList;
		std::vector<Scene*> scenes;

		UserList userList;
	};
}

