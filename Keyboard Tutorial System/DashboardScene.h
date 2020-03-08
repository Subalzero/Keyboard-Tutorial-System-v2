#pragma once

#include "Scene.h"
#include "TextToSpeech.h"
#include "UserList.h"

namespace rescan
{
	class DashboardScene : public Scene
	{
	public:
		struct DashBoardSceneContext
		{
			bool isExit;
			bool willDeleteUser;
			unsigned selectedLesson;
			unsigned selectedModule;
			User iser;
		};
		DashboardScene(Rect rect, Graphics2D* gfx, Keyboard* kbd, TextToSpeech* tts);
		~DashboardScene();
		void Draw() override;
		void Update(double deltaTime) override;
		void Begin() override;
		void Up();
		void Down();
		void Tab();
		void SetUser(User user);
		User GetUser();
		unsigned GetSelected();
		void KeyboardEvents(const Keyboard::Event& ev) override;
		std::wstring GetSelectedString();
	private:
		CComPtr<ID2D1SolidColorBrush> pWhiteBrush;
		CComPtr<ID2D1SolidColorBrush> pBlackBrush;
		CComPtr<ID2D1SolidColorBrush> pGray800Brush;
		CComPtr<ID2D1SolidColorBrush> pGray700Brush;
		CComPtr<ID2D1SolidColorBrush> pGray900Brush;
		CComPtr<ID2D1SolidColorBrush> pBlueBrush;
		CComPtr<ID2D1SolidColorBrush> pLightBlueBrush;
		CComPtr<ID2D1SolidColorBrush> pLightGrayBrush;
		CComPtr<IDWriteTextFormat> pTitleTextFormat;
		CComPtr<IDWriteTextFormat> pOptionTextFormat;

		Keyboard* kbd;
		TextToSpeech* tts;
		unsigned dashboardScreen;
		bool moduleIsRendering;

		User user;

		unsigned selectedSideOption;
		unsigned selectedModule;
		unsigned selectedLessonInMod1;
		unsigned selectedLessonInMod2;
		unsigned selectedLessonInMod3;
		unsigned selectedLessonInMod4;
		unsigned selectedLessonInMod5;
		unsigned selectedProgressItem;


		std::vector<std::wstring> sideOptions;
		std::vector<std::wstring> moduleNames;
		std::vector<std::wstring> module1Lessons;
		std::vector<std::wstring> module2Lessons;
		std::vector<std::wstring> module3Lessons;
		std::vector<std::wstring> module4Lessons;
		std::vector<std::wstring> module5Lessons;
		std::vector<std::wstring> progressList;
	};
}
