#pragma once

#include <string>
#include <vector>
#include <windows.h>

namespace Utils
{
	static std::string utf16ToUTF8(const std::wstring &s)
	{
		const int size = ::WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, nullptr, 0, nullptr, nullptr);

		std::vector<char> buf(size);
		::WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, &buf[0], size, nullptr, nullptr);

		return std::string(&buf[0]);
	}

	static std::string ExePath() {
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(nullptr, buffer, MAX_PATH);
		std::wstring wbuffer(buffer);
		std::string::size_type pos = std::string(wbuffer.begin(), wbuffer.end()).find_last_of("\\/");
		return std::string(wbuffer.begin(), wbuffer.end()).substr(0, pos);
	}
}