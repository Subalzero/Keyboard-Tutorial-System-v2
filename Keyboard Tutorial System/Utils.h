#pragma once

#include "stdafx.h"

#include <mutex>
#include <deque>

namespace rescan
{
	struct Size
	{
		double height;
		double width;
	};

	struct Origin
	{
		double x;
		double y;
	};

	struct Rect
	{
		Origin origin;
		Size size;
	};

	template <typename T>
	void SafeRelease(T& object)
	{
		if (object != nullptr)
		{
			object->Release();
			object = nullptr;
		}
	}

	void ThreadSafePop(std::deque<unsigned char*>& buffers);

	float PixelsToDIP(float pixels) noexcept;
	float DIPToPixels(float DIP) noexcept;

	void LoadFileInResource(LPCWSTR name, LPCWSTR type, DWORD* size, const char** data);
	std::istream& safeGetline(std::istream& is, std::string& t);
	std::wistream& safeGetline(std::wistream& wis, std::wstring& wt);
}




