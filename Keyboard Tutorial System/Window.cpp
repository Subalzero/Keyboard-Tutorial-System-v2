#include "stdafx.h"
#include "Window.h"

rescan::Window::WindowClass rescan::Window::WindowClass::wndClass;

const wchar_t* rescan::Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE rescan::Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}

rescan::Window::WindowClass::WindowClass() :
	hInstance(GetModuleHandle(NULL))
{
	WNDCLASSEX wcx = { 0 };
	wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcx.lpfnWndProc = HandleMessageSetup;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hIconSm = wcx.hIcon;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = wndClassName;
	wcx.cbSize = sizeof(WNDCLASSEX);

	if (RegisterClassEx(&wcx) == 0)
	{
		WND_LAST_EXCEPT();
	}

	SetProcessDPIAware();
	CoInitialize(NULL);
}

rescan::Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
	CoUninitialize();
}

// Window class

rescan::Window::Window(int width, int height, const wchar_t* name) :
	width(width),
	height(height)
{
	RECT wr;
	wr.left = 0;
	wr.top = 0;
	wr.right = width + wr.left;
	wr.bottom = height + wr.top;

	if (AdjustWindowRectEx(&wr,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		FALSE,
		WS_EX_APPWINDOW
	) == FALSE)
	{
		throw WND_LAST_EXCEPT();
	}

	// Create window & get hWnd
	hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		(LPCWSTR)WindowClass::GetName(),
		name,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		0,
		0,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		WindowClass::GetInstance(),
		this
	);

	if (hWnd == NULL)
	{
		throw WND_LAST_EXCEPT();
	}

	pGfx = new Graphics2D(hWnd, height, width);

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	// Register Mouse raw input
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	
	if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		throw WND_LAST_EXCEPT();
}

rescan::Window::~Window()
{
	if (pGfx)
	{
		delete pGfx;
		pGfx = nullptr;
	}
	DestroyWindow(hWnd);
}

void rescan::Window::SetTitle(const wchar_t* title)
{
	if (SetWindowText(hWnd, title) == FALSE)
		throw WND_LAST_EXCEPT();
}

void rescan::Window::EnableCursor() noexcept
{
	cursorEnabled = true;
	ShowCursor();
	FreeCursor();
}

void rescan::Window::DisableCursor() noexcept
{
	cursorEnabled = false;
	HideCursor();
	ConfineCursor();
}

bool rescan::Window::CursorEnabled() const noexcept
{
	return cursorEnabled;
}

std::optional<int> rescan::Window::ProcessMessages() noexcept
{
	MSG msg = { 0 };

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// Check for Quit Message
		if (msg.message == WM_QUIT)
		{
			// return the quit value.
			return (int)msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

rescan::Graphics2D* rescan::Window::Gfx()
{
	return pGfx;
}

void rescan::Window::ConfineCursor() noexcept
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	MapWindowPoints(hWnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
	ClipCursor(&rect);
}

void rescan::Window::FreeCursor() noexcept
{
	ClipCursor(NULL);
}

void rescan::Window::ShowCursor() noexcept
{
	while (::ShowCursor(TRUE) < 0);
}

void rescan::Window::HideCursor() noexcept
{
	while (::ShowCursor(FALSE) >= 0);
}

LRESULT rescan::Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT rescan::Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window instance.
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT rescan::Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	// we don't want the DefProc to handle this message because
	// we want our destructor to destroy the window, so return 0 instead of break
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	// clear keystate when window loses focus to prevent input getting "stuck"
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;
	case WM_ACTIVATE:
		// confine/free cursor on window to foreground/background if cursor disabled
		if (!cursorEnabled)
		{
			if (wParam & WA_ACTIVE)
			{
				ConfineCursor();
				HideCursor();
			}
			else
			{
				FreeCursor();
				ShowCursor();
			}
		}
		break;

	/**************** KEYBOARD MESSAGES ******************/
	case WM_KEYDOWN:
	// syskey commands need to be handled to track ALT key (VK_MENU) and F10
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // filter autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
	/*************** END KEYBOARD MESSAGES ****************/

	/************** MOUSE MESSAGES ******************/
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		// cursorless exclusive gets first dibs
		if (!cursorEnabled)
		{
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
				HideCursor();
			}
			break;
		}
		// in client region -> log move, and log enter + capture mouse (if not previously in window)
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// not in client -> log move / maintain capture if button down
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			// button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetForegroundWindow(hWnd);
		if (!cursorEnabled)
		{
			ConfineCursor();
			HideCursor();
		}
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
	/*************** END MOUSE MESSAGES ****************/

	/*************** RAW MOUSE MESSAGES ****************/
	case WM_INPUT:
	{
		if (!mouse.RawEnabled())
			break;

		UINT size;
		// first get the size of the input data.
		if (GetRawInputData(
			(HRAWINPUT)lParam,
			RID_INPUT,
			NULL,
			&size,
			sizeof(RAWINPUTHEADER)
		) == -1)
		{
			// bail message processing if error.
			break;
		}
		rawBuffer.resize(size);
		// read in the input data.
		if (GetRawInputData(
			(HRAWINPUT)lParam,
			RID_INPUT,
			rawBuffer.data(),
			&size,
			sizeof(RAWINPUTHEADER)
		) != size)
		{
			// bail message processing if error.
			break;
		}
		// process the raw input data.
		const RAWINPUT* ri = reinterpret_cast<const RAWINPUT*>(rawBuffer.data());
		if (ri->header.dwType == RIM_TYPEMOUSE &&
			ri->data.mouse.lLastX != 0 || ri->data.mouse.lLastY != 0)
		{
			mouse.OnRawDelta(ri->data.mouse.lLastX, ri->data.mouse.lLastY);
		}
		break;
	}
	/***************** END RAW INPUT MESSAGES ******************/
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

