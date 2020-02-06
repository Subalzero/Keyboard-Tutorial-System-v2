#pragma once

#include "stdafx.h"
#include "Utils.h"
#include "Exception.h"

namespace rescan
{
	class Graphics2D
	{
	public:
		Graphics2D(HWND hWnd, int height, int width);
		Graphics2D(const Graphics2D&) = delete;
		Graphics2D& operator=(const Graphics2D&) = delete;
		~Graphics2D();
		HWND GetWindow();
		ID2D1HwndRenderTarget* GetRenderTarget();
		ID2D1Factory* GetD2DFactory();
		IDWriteFactory* GetDWriteFactory();
		SIZE GetSize();
	private:
		HWND hWnd;
		ID2D1HwndRenderTarget* pRenderTarget;
		ID2D1Factory* pD2D1Factory;
		IDWriteFactory* pDWriteFactory;
		int height;
		int width;
	};
}
