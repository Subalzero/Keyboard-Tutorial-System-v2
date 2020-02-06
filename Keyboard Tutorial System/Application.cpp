#include "stdafx.h"
#include "Application.h"

rescan::Application::Application(const std::wstring& commandLine) :
	commandLine(commandLine),
	wnd(1920, 1080, L"Keyboard Tutorial")
{
}

int rescan::Application::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

rescan::Application::~Application()
{
}

void rescan::Application::DoFrame()
{
}
