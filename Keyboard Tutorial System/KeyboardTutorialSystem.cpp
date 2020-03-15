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

	lesson1 = std::make_unique<Lesson1>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson2 = std::make_unique<Lesson2>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson3 = std::make_unique<Lesson3>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson4 = std::make_unique<Lesson4>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson5 = std::make_unique<Lesson5>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson6 = std::make_unique<Lesson6>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson7 = std::make_unique<Lesson7>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson8 = std::make_unique<Lesson8>(rect, wnd.Gfx(), & wnd.kbd, & wnd.mouse, tts);
	lesson9 = std::make_unique<Lesson9>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson10 = std::make_unique<Lesson10>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson11 = std::make_unique<Lesson11>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson12 = std::make_unique<Lesson12>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson13 = std::make_unique<Lesson13>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson14 = std::make_unique<Lesson14>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson15 = std::make_unique<Lesson15>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson16 = std::make_unique<Lesson16>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson17 = std::make_unique<Lesson17>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson18 = std::make_unique<Lesson18>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson19 = std::make_unique<Lesson19>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson20 = std::make_unique<Lesson20>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson21 = std::make_unique<Lesson21>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson22 = std::make_unique<Lesson22>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson23 = std::make_unique<Lesson23>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson24 = std::make_unique<Lesson24>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson25 = std::make_unique<Lesson25>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson26 = std::make_unique<Lesson26>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson27 = std::make_unique<Lesson27>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson28 = std::make_unique<Lesson28>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson29 = std::make_unique<Lesson29>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson30 = std::make_unique<Lesson30>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson31 = std::make_unique<Lesson31>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson32 = std::make_unique<Lesson32>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson33 = std::make_unique<Lesson33>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson34 = std::make_unique<Lesson34>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson35 = std::make_unique<Lesson35>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson36 = std::make_unique<Lesson36>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson37 = std::make_unique<Lesson37>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson38 = std::make_unique<Lesson38>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson39 = std::make_unique<Lesson39>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson40 = std::make_unique<Lesson40>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lesson41 = std::make_unique<Lesson41>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	
	introLesson1 = std::make_unique<Introduction1>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	introLesson2 = std::make_unique<Introduction2>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	introLesson3 = std::make_unique<Introduction3>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	introLesson4 = std::make_unique<Introduction4>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	introLesson5 = std::make_unique<Introduction5>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	introLesson6 = std::make_unique<Introduction6>(rect, wnd.Gfx(), &wnd.kbd, &wnd.mouse, tts);
	lessonList.push_back(introLesson1.get());
	lessonList.push_back(introLesson2.get());
	lessonList.push_back(introLesson3.get());
	lessonList.push_back(introLesson4.get());
	lessonList.push_back(introLesson5.get());
	lessonList.push_back(introLesson6.get());
	lessonList.push_back(lesson1.get());
	lessonList.push_back(lesson2.get());
	lessonList.push_back(lesson3.get());
	lessonList.push_back(lesson4.get());
	lessonList.push_back(lesson5.get());
	lessonList.push_back(lesson6.get());
	lessonList.push_back(lesson7.get());
	lessonList.push_back(lesson8.get());
	lessonList.push_back(lesson9.get());
	lessonList.push_back(lesson10.get());
	lessonList.push_back(lesson11.get());
	lessonList.push_back(lesson12.get());
	lessonList.push_back(lesson13.get());
	lessonList.push_back(lesson14.get());
	lessonList.push_back(lesson15.get());
	lessonList.push_back(lesson16.get());
	lessonList.push_back(lesson17.get());
	lessonList.push_back(lesson18.get());
	lessonList.push_back(lesson19.get());
	lessonList.push_back(lesson20.get());
	lessonList.push_back(lesson21.get());
	lessonList.push_back(lesson22.get());
	lessonList.push_back(lesson23.get());
	lessonList.push_back(lesson24.get());
	lessonList.push_back(lesson25.get());
	lessonList.push_back(lesson26.get());
	lessonList.push_back(lesson27.get());
	lessonList.push_back(lesson28.get());
	lessonList.push_back(lesson29.get());
	lessonList.push_back(lesson30.get());
	lessonList.push_back(lesson31.get());
	lessonList.push_back(lesson32.get());
	lessonList.push_back(lesson33.get());
	lessonList.push_back(lesson34.get());
	lessonList.push_back(lesson35.get());
	lessonList.push_back(lesson36.get());
	lessonList.push_back(lesson37.get());
	lessonList.push_back(lesson38.get());
	lessonList.push_back(lesson39.get());
	lessonList.push_back(lesson40.get());
	lessonList.push_back(lesson41.get());

	for (size_t i = 0; i < lessonList.size(); ++i)
		lessonList[i]->callback = this;

	scoreScene = std::make_unique<ScoreScene>(rect, wnd.Gfx(), tts);
	scoreScene->callback = this;

	quitScene = std::make_unique<QuitMessageScene>(rect, wnd.Gfx(), tts);
	quitScene->callback = this;

	mainMenuScene = std::make_unique<MainMenuScene>(rect, wnd.Gfx(), tts, &wnd.kbd);
	mainMenuScene->callback = this;

	userListScene = std::make_unique<UserListScene>(rect, wnd.Gfx(), tts, &wnd.kbd, &userList);
	userListScene->callback = this;

	newUserScene = std::make_unique<NewUserScene>(rect, wnd.Gfx(), &wnd.kbd, tts);
	newUserScene->callback = this;

	deleteUserScene = std::make_unique<DeleteUserScene>(rect, wnd.Gfx(), tts);
	deleteUserScene->callback = this;

	dashboardScene = std::make_unique<DashboardScene>(rect, wnd.Gfx(), &wnd.kbd, tts);
	dashboardScene->callback = this;

	focusedScene = mainMenuScene.get();
	focusedScene->Begin();
	scenes.push_back(focusedScene);
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
			focusedScene = userListScene.get();
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
		else if (cont->willAddUser)
		{
			focusedScene = newUserScene.get();
			focusedScene->Begin();
			scenes.push_back(focusedScene);
		}
		else
		{
			dashboardScene->SetUser(cont->user);
			focusedScene = dashboardScene.get();
			focusedScene->Begin();
			scenes.push_back(focusedScene);
		}
	}
	else if (NewUserScene * sc = dynamic_cast<NewUserScene*>(scene))
	{
		NewUserScene::NewUserSceneContext* cont = reinterpret_cast<NewUserScene::NewUserSceneContext*>(context);
		if (cont->isExit)
		{
			scenes.pop_back();
			focusedScene = scenes.back();
			focusedScene->Begin();
			return;
		}
		else
		{
			bool hasNotUser = userList.AddEmptyUser(cont->userName);
			if (hasNotUser)
			{
				scenes.pop_back();
				focusedScene = scenes.back();
				focusedScene->Begin();
			}
			else
				tts->speak(L"User already exists. Please try a different username.", TTSFLAGS_ASYNC | TTSFLAGS_PURGEBEFORESPEAK);
		}
	}
	else if (DashboardScene * sc = dynamic_cast<DashboardScene*>(scene))
	{
		DashboardScene::DashboardSceneContext* cont = reinterpret_cast<DashboardScene::DashboardSceneContext*>(context);
		if (cont->isExit)
		{
			scenes.pop_back();
			focusedScene = scenes.back();
			focusedScene->Begin();
			return;
		}
		else if (cont->willDeleteUser)
		{
			deleteUserScene->SetUser(cont->user);
			focusedScene = deleteUserScene.get();
			focusedScene->Begin();
			return;
		}
		ILesson* lesson = nullptr;
		if (cont->selectedModule == 0)
		{
			int l = -cont->selectedLesson;
			lesson = lessonList[l];
		}
		else
		{
			lesson = lessonList[cont->selectedLesson + 6];
		}
		scenes.push_back(lesson);
		lesson->Begin();
		focusedScene = lesson;
	}
	else if (DeleteUserScene * sc = dynamic_cast<DeleteUserScene*>(scene))
	{
		DeleteUserScene::DeleteUserSceneContext* cont = reinterpret_cast<DeleteUserScene::DeleteUserSceneContext*>(context);
		if (cont->returnType == DeleteUserScene::Type::DeleteUserScene_OK)
		{
			userList.RemoveUser(cont->user.userID);
			scenes.pop_back();
			focusedScene = scenes.back();
			focusedScene->Begin();
		}
		else
		{
			focusedScene = scenes.back();
		}
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
		else if (cont->isTutorial)
		{
			scenes.pop_back();
			focusedScene = scenes.back();
		}
		else
		{
			scenes.pop_back();
			double accuracy = (double(cont->totalChars) - double(cont->errors)) / double(cont->totalChars) * 100.f;
			scoreScene->SetScore(cont->totalTime, cont->wordsPerMinute, accuracy);
			BestScore score = { 0 };
			score.parTime = cont->totalTime;
			score.wordsPerMinute = cont->wordsPerMinute;
			score.accuracy = accuracy;
			score.frequency = ++dashboardScene->GetUser().scores->frequency;
			userList.AddUserScore(score, menuScene->GetUser().userID, cont->lesson);
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
