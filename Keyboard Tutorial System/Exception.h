#pragma once

#include <exception>
#include <string>

namespace rescan
{
	class Exception : public std::exception
	{
	public:
		Exception(int line, const char* file) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;
	private:
		int line;
		std::string file;
	protected:
		mutable std::string whatBuffer;
	};

	class HResultException : public Exception
	{
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HResultException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
}

#define WND_EXCEPT(hr) rescan::HResultException::HResultException(__LINE__, __FILE__, (hr))
#define WND_LAST_EXCEPT() rescan::HResultException::HResultException(__LINE__, __FILE__, GetLastError())

