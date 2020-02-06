#pragma once

#include "stdafx.h"
#include "Exception.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics2D.h"
#include <memory>

namespace rescan
{
	class Window
	{
	private:
		// Singleton manages registration/cleanup of window class
		class WindowClass
		{
		public:
			static const wchar_t* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass();
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const wchar_t* wndClassName = L"KeyTut";
			static WindowClass wndClass;
			HINSTANCE hInstance;
		};
	public:
		Window(int width, int height, const wchar_t* name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		void SetTitle(const wchar_t* title);
		void EnableCursor() noexcept;
		void DisableCursor() noexcept;
		bool CursorEnabled() const noexcept;
		static std::optional<int> ProcessMessages() noexcept;
		Graphics2D* Gfx();
	private:
		void ConfineCursor() noexcept;
		void FreeCursor() noexcept;
		void ShowCursor() noexcept;
		void HideCursor() noexcept;

		static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	public:
		Keyboard kbd;
		Mouse mouse;
	private:
		bool cursorEnabled = true;
		int width;
		int height;
		HWND hWnd;
		Graphics2D* pGfx;
		std::vector<BYTE> rawBuffer;
		std::string commandLine;
	};
}
