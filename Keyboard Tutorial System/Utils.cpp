#include "stdafx.h"
#include "Utils.h"
#include "Exception.h"

std::mutex mut;

void rescan::ThreadSafePop(std::deque<unsigned char*>& buffers)
{
	std::lock_guard<std::mutex> lock(mut);
	if (buffers.size() != 0)
	{
		unsigned char* pData = buffers.front();
		buffers.pop_front();
		delete[] pData;
	}
}

float rescan::PixelsToDIP(float pixels) noexcept
{
	UINT dpi = GetDpiForSystem();
	return pixels * 96.f / dpi;
}

float rescan::DIPToPixels(float DIP) noexcept
{
	UINT dpi = GetDpiForSystem();
	return DIP * dpi / 96.f;
}

void rescan::LoadFileInResource(LPCWSTR name, LPCWSTR type, DWORD* size, const char** data)
{
	*data = nullptr;
	HMODULE handle = GetModuleHandle(NULL);
	HRSRC rc = FindResource(handle, name, type);
	if (!rc)
		throw WND_LAST_EXCEPT();
	HGLOBAL rcData = LoadResource(handle, rc);
	if (!rcData)
		throw WND_LAST_EXCEPT();
	*size = SizeofResource(handle, rc);
	*data = static_cast<const char*>(LockResource(rcData));
	if (!*data)
		throw WND_LAST_EXCEPT();
	FreeResource(rcData);
}

std::istream& rescan::safeGetline(std::istream& is, std::string& t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::istream::sentry se(is, true);
	std::streambuf* sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
		case '\n':
			return is;
		case '\r':
			if (sb->sgetc() == '\n')
				sb->sbumpc();
			return is;
		case std::streambuf::traits_type::eof():
			// Also handle the case when the last line has no line ending
			if (t.empty())
				is.setstate(std::ios::eofbit);
			return is;
		default:
			t += (char)c;
		}
	}
}

std::wistream& rescan::safeGetline(std::wistream& wis, std::wstring& wt)
{
	wt.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::wistream::sentry wse(wis, true);
	std::wstreambuf* wsb = wis.rdbuf();

	for (;;)
	{
		int wc = wsb->sbumpc();
		switch (wc)
		{
		case L'\n':
			return wis;
		case L'\r':
			if (wsb->sgetc() == L'\n')
				wsb->sbumpc();
			return wis;
		case std::wstreambuf::traits_type::eof():
			// Also handle the case when the last line has no line ending
			if (wt.empty())
				wis.setstate(std::wios::eofbit);
			return wis;
		default:
			wt += (wchar_t)wc;
		}
	}
}
