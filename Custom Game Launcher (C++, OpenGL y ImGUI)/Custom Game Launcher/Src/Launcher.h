#pragma once

#include <string>
#include <iostream>

#include <Windows.h>
#include <WinInet.h>
#include <shellapi.h>

#include <tlhelp32.h>

#include "Utils.h"


class Launcher
{
public:
	enum Platform { Steam, BattleNet, EpicGames, UPlay, Origin, GOG, Glyph, LOL };

	static bool launcherRunning;

private:
	std::string name;
	Image* image;
	Platform platform;
	std::string path;

public:
	Launcher(std::string name, Platform platform, std::string launcherPath) :
		name(name), image(0), platform(platform), path(launcherPath) 
	{
		if (std::filesystem::exists(std::filesystem::current_path() / ("icons\\" + name + ".png")))
		{
			switch (platform)
			{
			case Steam:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "files.softicons.com",
					std::string("/download/system-icons/omnom-icons-by-ampeross/png/256x256/steam.png").c_str()))
					return;
				break;
			case BattleNet:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "img10.androidappsapk.co",
					std::string("/300/b/8/7/com.blizzard.messenger.png").c_str()))
					return;
				break;
			case GOG:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "icon-library.net",
					std::string("/images/gog-icon/gog-icon-21.jpg").c_str()))
					return;
				break;
			case Origin:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "files.softicons.com",
					std::string("/download/system-icons/omnom-icons-by-ampeross/png/256x256/origin.png").c_str()))
					return;
				break;
			case LOL:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "res.cloudinary.com",
					std::string("/gamestry/image/upload/v1539948752/games/league_of_legends/lol-logo.png").c_str()))
					return;
				break;
			case EpicGames:
				if (!downloadFileFromUrl(std::string("icons\\" + name + ".png").c_str(), "i.pinimg.com",
					std::string("/originals/21/2d/1b/212d1b4d8d3f8ec990eb405e735b3f8d.png").c_str()))
					return;
				break;
			default:
				break;
			}
		}

		image = new Image(std::string("icons\\" + name + ".png").c_str());
	}

	void loadTexture()
	{
		image->loadTexture();
	}

	inline std::string getName() { return name; }
	inline unsigned int getCover() { return image->getTextureId(); }
	inline Platform getPlatform() { return platform; }

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

#if BLOCK_START == 1
		if (success != 0)
		{
			gameRunning = true;

			WaitForInputIdle(processInfo.hProcess, 10000);
			DWORD exitCode = 0;
			if (GetExitCodeProcess(processInfo.hProcess, &exitCode) && exitCode != STILL_ACTIVE)
			{
				gameRunning = false;
			}
		}
#else
		if (success != 0)
		{
			launcherRunning = true;
			Sleep(2000);
			launcherRunning = false;
		}
#endif

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		if (success != 0)
			return true;

		return false;
	}
};

bool Launcher::launcherRunning = false;