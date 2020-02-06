#include "stdafx.h"
#include "Graphics2D.h"

#define CHECK_HRESULT(hr) if (FAILED(hr)) throw WND_EXCEPT(hr)

rescan::Graphics2D::Graphics2D(HWND hWnd, int height, int width) :
	hWnd(hWnd),
	height(height),
	width(width),
	pRenderTarget(nullptr),
	pD2D1Factory(nullptr),
	pDWriteFactory(nullptr)
{
	HRESULT hr;

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2D1Factory
	);

	CHECK_HRESULT(hr);

	RECT rect;
	GetClientRect(hWnd, &rect);

	D2D1_SIZE_U size = { rect.right - rect.left, rect.bottom - rect.top };

	hr = pD2D1Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			size
		),
		&pRenderTarget
	);

	CHECK_HRESULT(hr);

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	);

	CHECK_HRESULT(hr);
}

rescan::Graphics2D::~Graphics2D()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
	if (pD2D1Factory)
	{
		pD2D1Factory->Release();
		pD2D1Factory = nullptr;
	}
	if (pDWriteFactory)
	{
		pDWriteFactory->Release();
		pDWriteFactory = nullptr;
	}
}

HWND rescan::Graphics2D::GetWindow()
{
	return hWnd;
}

ID2D1HwndRenderTarget* rescan::Graphics2D::GetRenderTarget()
{
	return pRenderTarget;
}

ID2D1Factory* rescan::Graphics2D::GetD2DFactory()
{
	return pD2D1Factory;
}

IDWriteFactory* rescan::Graphics2D::GetDWriteFactory()
{
	return pDWriteFactory;
}

SIZE rescan::Graphics2D::GetSize()
{
	return { height, width };
}
