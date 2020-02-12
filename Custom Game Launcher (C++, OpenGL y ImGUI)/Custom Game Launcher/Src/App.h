#pragma once

#include <string>
#include <iostream>

#include <Windows.h>
#include <WinInet.h>
#include <shellapi.h>

#include <tlhelp32.h>

#include "Utils.h"


class App
{
public:
	enum Platform { Spotify, Discord };

private:
	std::string name;
	Platform platform;
	std::string path;

public:
	App(std::string name, Platform platform, std::string launcherPath) :
		name(name), platform(platform), path(launcherPath) {}

	bool Launch()
	{
		// Execute app process
		int success = 0;

		STARTUPINFO startupInfo;
		PROCESS_INFORMATION processInfo;

		ZeroMemory(&startupInfo, sizeof(startupInfo));
		startupInfo.cb = sizeof(startupInfo);
		ZeroMemory(&processInfo, sizeof(processInfo));

		success = CreateProcess(path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

		if (success == 0)
		{
			std::cout << "ERROR: " << GetLastError() << std::endl;
		}

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		if (success != 0)
			return true;

		return false;
	}
};