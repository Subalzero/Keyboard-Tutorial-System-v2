#include "stdafx.h"
#include "Exception.h"

#include <sstream>

rescan::Exception::Exception(int line, const char* file) noexcept :
	line(line),
	file(file)
{
}

const char* rescan::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* rescan::Exception::GetType() const noexcept
{
	return "Rescan Exception";
}

int rescan::Exception::GetLine() const noexcept
{
	return line;
}

const std::string& rescan::Exception::GetFile() const noexcept
{
	return file;
}

std::string rescan::Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl
		<< "[Line]" << line;
	return oss.str();
}

std::string rescan::HResultException::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;

	const DWORD nMsgLen = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)& pMsgBuf,
		0,
		NULL
	);

	if (nMsgLen == 0)
		return "Unidentified error code";

	std::string errorString = pMsgBuf;

	LocalFree(pMsgBuf);

	return errorString;
}

rescan::HResultException::HResultException(int line, const char* file, HRESULT hr) noexcept :
	Exception(line, file),
	hr(hr)
{
}

const char* rescan::HResultException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* rescan::HResultException::GetType() const noexcept
{
	return "Rescan Window Exception";
}

HRESULT rescan::HResultException::GetErrorCode() const noexcept
{
	return hr;
}

std::string rescan::HResultException::GetErrorDescription() const noexcept
{
	return TranslateErrorCode(hr);
}
