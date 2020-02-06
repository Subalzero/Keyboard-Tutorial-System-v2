#include "stdafx.h"
#include "vld.h"
#include "TextToSpeech.h"
#include "Window.h"
#include "KeyboardTutorialSystem.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pScmdline, int iCmdShow)
{
	try {
		rescan::KeyboardTutorialSystem app;
		app.Go();
	}
	catch (rescan::Exception& e)
	{
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}