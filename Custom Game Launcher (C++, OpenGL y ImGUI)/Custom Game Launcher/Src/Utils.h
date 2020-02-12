#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/stb_image.h"

static std::string steamInstallationPath;
static std::string gogInstallationPath;
static std::string battleNetInstallationPath;
static std::string originInstallationPath;

class Image
{
	const char* path;
	unsigned int textureId;
	unsigned short* data;
	int width;
	int height;
	int components;

public:
	Image(char const* path) :
		textureId(0), width(0), height(0), components(0)
	{
		this->path = path;
		data = stbi_load_16(path, &width, &height, &components, 0);

		if(!data)
			std::cout << "Texture failed to load at path: " << path << std::endl;
	}

	unsigned int loadTexture()
	{
		if (data)
		{
			glGenTextures(1, &textureId);

			GLenum format = GL_RGB;
			if (components == 3)
				format = GL_RGB;
			else if (components == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_SHORT, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			free(data);

			return textureId;
		}

		return 0;
	}

	void deleteTexture()
	{
		glDeleteTextures(1, &textureId);
	}

	inline unsigned int getTextureId() const { return textureId; }
	inline const char* getPath() const { return path; }
};

static std::string stringTrim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

static size_t stringSplit(const std::string& txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

static std::string stringRemoveSPChar(std::string string)
{
	std::string newString;

	for (int i = 0; i < string.length(); i++)
	{
		char c = string[i];
		if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')
			newString += c;
	}

	return newString;
}

std::string stringUrlDecode(const char* src)
{
	std::string newString;
	char a, b;
	while (*src) {
		if ((*src == '%') &&
			((a = src[1]) && (b = src[2])) &&
			(isxdigit(a) && isxdigit(b))) {
			if (a >= 'a')
				a -= 'a' - 'A';
			if (a >= 'A')
				a -= ('A' - 10);
			else
				a -= '0';
			if (b >= 'a')
				b -= 'a' - 'A';
			if (b >= 'A')
				b -= ('A' - 10);
			else
				b -= '0';
			newString += 16 * a + b;
			src += 3;
		}
		else if (*src == '+') {
			newString += ' ';
			src++;
		}
		else {
			newString += *src++;
		}
	}
	
	return newString;
}

std::string getRegisterKey(HKEY registryKey, const char* registry, const char* key)
{
	HKEY hRegKey = NULL;
	HKEY hAppKey = NULL;
	DWORD LongestValueName = 1024;
	LPSTR sValue = new char[LongestValueName];
	LPCSTR sRoot = registry;
	long lResult = ERROR_SUCCESS;
	DWORD dwType = KEY_ALL_ACCESS;
	DWORD dwBufferSize = 0;

	if (RegOpenKeyEx(registryKey, sRoot, 0, KEY_READ, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(registryKey, sRoot, 0, KEY_READ, &hAppKey) != ERROR_SUCCESS)
		{
			RegCloseKey(hAppKey);
			RegCloseKey(hRegKey);
		}

		dwBufferSize = LongestValueName;
		RegQueryValueEx(hAppKey, key, NULL, &dwType, (unsigned char*)sValue, &dwBufferSize);

		RegCloseKey(hAppKey);
	}

	RegCloseKey(hRegKey);

	return std::string(sValue);
}

std::vector<std::string> getRegisterSubKeys(HKEY registryKey, const char* registry, const char* key)
{
	std::vector<std::string> values;

	HKEY hRegKey = NULL;
	HKEY hAppKey = NULL;
	DWORD LongestValueName = 1024;
	LPSTR sAppKeyName = new char[LongestValueName];
	LPSTR sSubKey = new char[LongestValueName];
	LPSTR sValue = new char[LongestValueName];
	LPCSTR sRoot = registry;
	long lResult = ERROR_SUCCESS;
	DWORD dwType = KEY_ALL_ACCESS;
	DWORD dwBufferSize = 0;

	if (RegOpenKeyEx(registryKey, sRoot, 0, KEY_READ, &hRegKey) == ERROR_SUCCESS)
	{
		for (DWORD dwIndex = 0; lResult == ERROR_SUCCESS; dwIndex++)
		{
			dwBufferSize = LongestValueName;
			if ((lResult = RegEnumKeyEx(hRegKey, dwIndex, sAppKeyName,
				&dwBufferSize, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS)
			{
				wsprintf(sSubKey, "%s\\%s", sRoot, sAppKeyName);
				if (RegOpenKeyEx(registryKey, sSubKey, 0, KEY_READ, &hAppKey) != ERROR_SUCCESS)
				{
					RegCloseKey(hAppKey);
					RegCloseKey(hRegKey);
					break;
				}

				dwBufferSize = LongestValueName;
				if (RegQueryValueEx(hAppKey, key, NULL,
					&dwType, (unsigned char*)sValue, &dwBufferSize) == ERROR_SUCCESS)
				{
					values.emplace_back(sValue);
				}

				RegCloseKey(hAppKey);
			}
		}
	}

	RegCloseKey(hRegKey);

	return values;
}

std::vector<std::vector<std::string>> getRegisterMultipleSubKeys(HKEY registryKey, const char* registry, std::vector<const char*> keys)
{
	std::vector<std::vector<std::string>> values;

	HKEY hRegKey = NULL;
	HKEY hAppKey = NULL;
	DWORD LongestValueName = 1024;
	LPSTR sAppKeyName = new char[LongestValueName];
	LPSTR sSubKey = new char[LongestValueName];
	LPSTR sValue = new char[LongestValueName];
	LPCSTR sRoot = registry;
	long lResult = ERROR_SUCCESS;
	DWORD dwType = KEY_ALL_ACCESS;
	DWORD dwBufferSize = 0;

	if (RegOpenKeyEx(registryKey, sRoot, 0, KEY_READ, &hRegKey) == ERROR_SUCCESS)
	{
		for (DWORD dwIndex = 0; lResult == ERROR_SUCCESS; dwIndex++)
		{
			dwBufferSize = LongestValueName;
			if ((lResult = RegEnumKeyEx(hRegKey, dwIndex, sAppKeyName,
				&dwBufferSize, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS)
			{
				wsprintf(sSubKey, "%s\\%s", sRoot, sAppKeyName);
				if (RegOpenKeyEx(registryKey, sSubKey, 0, KEY_READ, &hAppKey) != ERROR_SUCCESS)
				{
					RegCloseKey(hAppKey);
					RegCloseKey(hRegKey);
					break;
				}

				std::vector<std::string> subKeys;
				for (const char* key : keys)
				{
					dwBufferSize = LongestValueName;
					RegQueryValueEx(hAppKey, key, NULL, &dwType, (unsigned char*)sValue, &dwBufferSize);

					subKeys.emplace_back(sValue);
				}
				values.emplace_back(subKeys);

				RegCloseKey(hAppKey);
			}
		}
	}

	RegCloseKey(hRegKey);

	return values;
}

std::vector<std::string> getInstalledPrograms()
{
	return getRegisterSubKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall", "DisplayName");
}

bool downloadFileFromUrl(const char* filePath, const char* url, const char* webDirectories)
{
	bool success = false;
	HINTERNET Initialize, Connection, File;
	DWORD dwBytes;

	char ch;
	Initialize = InternetOpen("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!Initialize)
	{
		std::cout << "Error opening valid internet connection: " << GetLastError() << std::endl;
		return false;
	}

	Connection = InternetConnect(Initialize, url, INTERNET_DEFAULT_HTTP_PORT,
		NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	File = HttpOpenRequest(Connection,
		"GET",
		webDirectories,
		"HTTP/1.1",
		NULL, NULL,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);

	if (HttpSendRequest(File, NULL, 0, NULL, 0))
	{
		std::ofstream webSource;
		webSource.open(filePath, std::ofstream::binary | std::ofstream::trunc);

		if (webSource.is_open()) {
			while (InternetReadFile(File, &ch, 1, &dwBytes))
			{
				if (dwBytes != 1) break;
				webSource << ch;
			}
			webSource.close();

			success = true;
		}
	}

	InternetCloseHandle(File);
	InternetCloseHandle(Connection);
	InternetCloseHandle(Initialize);

	return success;
}

std::string requestIGDB(std::string query)
{
	int success = 0;

	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	LPSTR arguments = NULL;

	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));

	HANDLE outputRead = NULL;
	HANDLE outputWrite = NULL;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	if (!CreatePipe(&outputRead, &outputWrite, &sa, 0)) {
		return "";
	}
	if (!SetHandleInformation(outputRead, HANDLE_FLAG_INHERIT, 0)) {
		return "";
	}

	startupInfo.hStdOutput = outputWrite;
	startupInfo.dwFlags |= STARTF_USESTDHANDLES;

	std::string pathArguments("C:\\Windows\\System32\\cmd.exe /c"
		" curl \"https://api-v3.igdb.com/games\""
		" -H \"user-key: 9cf3aea4b3f1cfd73d4518fc8341b860\""
		" -H \"Accept: application/json\""
		" -d \"" + query + "\"");

	arguments = new char[pathArguments.length() + 1];
	pathArguments.copy(arguments, pathArguments.length() + 1);
	arguments[pathArguments.length()] = '\0';

	std::string out = "";
	success = CreateProcess("C:\\Windows\\System32\\cmd.exe", arguments, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInfo);

	if (success != 0)
	{
		WaitForSingleObject(processInfo.hProcess, 10000);

		DWORD dwRead;
		CHAR chBuf[4096];
		bool bSuccess = FALSE;

		do {
			bSuccess = ReadFile(outputRead, chBuf, 4096, &dwRead, NULL);

			std::string s(chBuf, dwRead);
			out += s;
		} while (bSuccess && dwRead == 4096);
	}

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

	return out;
}