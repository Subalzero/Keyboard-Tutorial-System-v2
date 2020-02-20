#include "stdafx.h"
#include "KeyboardTutorialSystem.h"

rescan::KeyboardTutorialSystem::KeyboardTutorialSystem(const std::wstring& commandLine) :
	tts(nullptr),
	focusedScene(nullptr)
{
	tts = new TextToSpeech(SPCAT_VOICES_ONECORE, 1);

	RECT rc;
	GetClientRect(wnd.Gfx()->GetWindow(), &rc);
	Rect rect;
	rect.origin.x = rc.left;
	rect.origin.y = rc.top;
	rect.size.width = double(rc.right) - (double)rc.left;
	rect.size.height = double(rc.bottom) - (double)rc.top;
	menuScene = new GameMenuScene(rect, wnd.Gfx(), &wnd.kbd, tts);
	menuScene->callback = this;

	lesson1 = new Lesson1(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson2 = new Lesson2(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson3 = new Lesson3(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson4 = new Lesson4(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson5 = new Lesson5(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson6 = new Lesson6(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson7 = new Lesson7(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson8 = new Lesson8(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson9 = new Lesson9(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson10 = new Lesson10(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson11 = new Lesson11(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson12 = new Lesson12(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson13 = new Lesson13(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson14 = new Lesson14(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson15 = new Lesson15(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson16 = new Lesson16(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson17 = new Lesson17(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson18 = new Lesson18(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson19 = new Lesson19(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson20 = new Lesson20(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson21 = new Lesson21(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson22 = new Lesson22(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson23 = new Lesson23(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson24 = new Lesson24(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson25 = new Lesson25(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson26 = new Lesson26(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson27 = new Lesson27(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson28 = new Lesson28(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson29 = new Lesson29(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson30 = new Lesson30(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson31 = new Lesson31(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson32 = new Lesson32(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson33 = new Lesson33(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson34 = new Lesson34(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson35 = new Lesson35(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson36 = new Lesson36(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson37 = new Lesson37(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson38 = new Lesson38(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson39 = new Lesson39(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson40 = new Lesson40(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson41 = new Lesson41(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson42 = new Lesson42(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson43 = new Lesson43(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lessonList.push_back(lesson1);
	lessonList.push_back(lesson2);
	lessonList.push_back(lesson3);
	lessonList.push_back(lesson4);
	lessonList.push_back(lesson5);
	lessonList.push_back(lesson6);
	lessonList.push_back(lesson7);
	lessonList.push_back(lesson8);
	lessonList.push_back(lesson9);
	lessonList.push_back(lesson10);
	lessonList.push_back(lesson11);
	lessonList.push_back(lesson12);
	lessonList.push_back(lesson13);
	lessonList.push_back(lesson14);
	lessonList.push_back(lesson15);
	lessonList.push_back(lesson16);
	lessonList.push_back(lesson17);
	lessonList.push_back(lesson18);
	lessonList.push_back(lesson19);
	lessonList.push_back(lesson20);
	lessonList.push_back(lesson21);
	lessonList.push_back(lesson22);
	lessonList.push_back(lesson23);
	lessonList.push_back(lesson24);
	lessonList.push_back(lesson25);
	lessonList.push_back(lesson26);
	lessonList.push_back(lesson27);
	lessonList.push_back(lesson28);
	lessonList.push_back(lesson29);
	lessonList.push_back(lesson30);
	lessonList.push_back(lesson31);
	lessonList.push_back(lesson32);
	lessonList.push_back(lesson33);
	lessonList.push_back(lesson34);
	lessonList.push_back(lesson35);
	lessonList.push_back(lesson36);
	lessonList.push_back(lesson37);
	lessonList.push_back(lesson38);
	lessonList.push_back(lesson39);
	lessonList.push_back(lesson40);
	lessonList.push_back(lesson41);
	lessonList.push_back(lesson42);
	lessonList.push_back(lesson43);

	for (size_t i = 0; i < lessonList.size(); ++i)
		lessonList[i]->callback = this;

	scoreScene = std::make_unique<ScoreScene>(rect, wnd.Gfx(), tts);
	scoreScene->callback = this;

	quitScene = std::make_unique<QuitMessageScene>(rect, wnd.Gfx(), tts);
	quitScene->callback = this;

	mainMenuScene = std::make_unique<MainMenuScene>(rect, wnd.Gfx(), tts, &wnd.kbd);
	mainMenuScene->callback = this;

	userListScene = std::make_unique<UserListScene>(rect, wnd.Gfx(), tts, &wnd.kbd);
	userListScene->callback = this;

	focusedScene = mainMenuScene.get();
	mainMenuScene->Begin();
	scenes.push_back(mainMenuScene.get());
}

rescan::KeyboardTutorialSystem::~KeyboardTutorialSystem()
{
	if (tts)
	{
		delete tts;
		tts = nullptr;
	}
	if (menuScene)
	{
		delete menuScene;
		menuScene = nullptr;
	}
	for (size_t i = 0; i < lessonList.size(); ++i)
		delete lessonList[i];
}

void rescan::KeyboardTutorialSystem::SetFocusedScene(Scene* scene)
{
	focusedScene = scene;
}

void rescan::KeyboardTutorialSystem::DoFrame()
{
	LARGE_INTEGER PCFreq = { 0 };
	QueryPerformanceFrequency(&PCFreq);
	if (focusedScene)
	{
		LARGE_INTEGER liStart = { 0 }, liEnd = { 0 };
		double freq, start, end;
		QueryPerformanceCounter(&liStart);
		freq = double(PCFreq.QuadPart);
		Graphics2D* gfx = wnd.Gfx();
		gfx->GetRenderTarget()->BeginDraw();
		D2D1_COLOR_F color = { 0.f, 0.f, 0.f, 1.f };
		gfx->GetRenderTarget()->Clear(color);
		focusedScene->Draw();
		gfx->GetRenderTarget()->EndDraw();
		while (const auto e = wnd.kbd.ReadKey())
		{
			focusedScene->KeyboardEvents(*e);
		}
		while (const auto e = wnd.mouse.Read())
		{
			focusedScene->MouseEvents(*e);
		}
		start = double(liStart.QuadPart);
		QueryPerformanceCounter(&liEnd);
		end = double(liEnd.QuadPart);
		focusedScene->Update((end - start) / freq);
		//std::wstringstream wss;
		//wss << L"Frame rate: " << 1 / ((end - start) / freq) << std::endl;
		//OutputDebugStringW(wss.str().c_str());
	}
}

void rescan::KeyboardTutorialSystem::SceneHasBegun(Scene* scene, void* context)
{
}

void rescan::KeyboardTutorialSystem::SceneHasEnded(Scene* scene, void* context)
{
	if (MainMenuScene * sc = dynamic_cast<MainMenuScene*>(scene))
	{
		MainMenuScene::MainMenuSceneContext* cont = reinterpret_cast<MainMenuScene::MainMenuSceneContext*>(context);
		if (cont->isExit)
		{
			focusedScene = quitScene.get();
			quitScene->Begin();
			return;
		}
		if (cont->index == 0)
		{
			focusedScene = menuScene;
			focusedScene->Begin();
			scenes.push_back(focusedScene);
		}
		else if (cont->index == 1)
		{
			focusedScene = quitScene.get();
			quitScene->Begin();
		}
	}
	else if (UserListScene * sc = dynamic_cast<UserListScene*>(scene))
	{
		UserListScene::UserListSceneContext* cont = reinterpret_cast<UserListScene::UserListSceneContext*>(context);
		if (cont->isExit)
		{
			scenes.pop_back();
			focusedScene = scenes.back();
			focusedScene->Begin();
			return;
		}
	}
	else if (GameMenuScene * sc = dynamic_cast<GameMenuScene*>(scene))
	{
		GameMenuScene::GameMenuSceneContext* cont = reinterpret_cast<GameMenuScene::GameMenuSceneContext*>(context);
		if (cont->isExit)
		{
			scenes.pop_back();
			focusedScene = scenes.back();
			focusedScene->Begin();
			return;
		}
		ILesson* lesson = lessonList[cont->selectedLesson];
		scenes.push_back(lesson);
		lesson->Begin();
		focusedScene = lesson;
	}
	else if (ILesson * sc = dynamic_cast<ILesson*>(scene))
	{
		ILesson::LessonContext* cont = reinterpret_cast<ILesson::LessonContext*>(context);
		if (cont->isExit)
		{
			focusedScene = quitScene.get();
			quitScene->Begin();
			return;
		}
		else
		{
			scenes.pop_back();
			double accuracy = (double(cont->totalChars) - double(cont->errors)) / double(cont->totalChars) * 100.f;
			scoreScene->SetScore(cont->totalTime, cont->wordsPerMinute, accuracy);
			scoreScene->Begin();
			scenes.push_back(scoreScene.get());
			focusedScene = scoreScene.get();
		}
	}
	else if (ScoreScene * sc = dynamic_cast<ScoreScene*>(scene))
	{
		scenes.pop_back();
		Scene* lastScene = scenes.back();
		focusedScene = lastScene;
	}
	else if (QuitMessageScene * sc = dynamic_cast<QuitMessageScene*>(scene))
	{
		QuitMessageScene::QuitMessageSceneContext* cont =
			reinterpret_cast<QuitMessageScene::QuitMessageSceneContext*>(context);
		if (MainMenuScene * prevScene = dynamic_cast<MainMenuScene*>(scenes.back()))
		{
			if (cont->returnType == QuitMessageScene::Type::QuitMessageScene_OK)
			{
				PostQuitMessage(0);
			}
			else
			{
				focusedScene = scenes.back();
			}
		}
		else if (ILesson * prevScene = dynamic_cast<ILesson*>(scenes.back()))
		{
			if (cont->returnType == QuitMessageScene::Type::QuitMessageScene_OK)
			{
				scenes.pop_back();
				focusedScene = scenes.back();
			}
			else
			{
				focusedScene = scenes.back();
				prevScene->Resume();
			}
		}
	}
}
