#pragma once

#include <string>
#include <unordered_map>
#include "Window.h"
#include "Drawable.h"

namespace rescan
{
	class Application
	{
	public:
		Application(const std::wstring& commandLine = L"");
		// master frame / message loop
		int Go();
		virtual ~Application();
	protected:
		virtual void DoFrame();
	protected:
		std::wstring commandLine;
		Window wnd;
		std::unordered_map <Drawable*, Drawable*> drawableObjects;
	};
}
