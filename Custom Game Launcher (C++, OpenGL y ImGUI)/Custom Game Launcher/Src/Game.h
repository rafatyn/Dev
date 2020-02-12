#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <stdio.h>

#include <Windows.h>
#include <WinInet.h>
#include <shellapi.h>

#include <tlhelp32.h>

#include "Utils.h"


class Game
{
public:
	enum Platform { Steam, BattleNet, EpicGames, Origin, GOG, Custom, LOL };

	static bool gameRunning;

private:
	std::string name;
	Image* image;
	Platform platform;
	std::string path;

	void getSteamImageIcon(std::string steamID)
	{
		if (!std::filesystem::exists(std::filesystem::current_path() / ("data\\" + steamID + ".jpg")))
		{
			if (!downloadFileFromUrl(std::string("data\\" + steamID + ".jpg").c_str(), "steamcdn-a.akamaihd.net", 
				std::string("/steam/apps/" + steamID + "/header.jpg").c_str()))
				return;
		}

		image = new Image(std::string("data\\" + steamID + ".jpg").c_str());
	}

	void getLOLImageIcon()
	{
		if (!std::filesystem::exists(std::filesystem::current_path() / ("data\\lol.jpg")))
		{
			if (!downloadFileFromUrl("data\\lol.jpg", "juanbeltran2016.files.wordpress.com", "/2016/02/cl4uthu.jpg"))
				return;
		}

		image = new Image(std::string("data\\lol.jpg").c_str());
	}

	void getSteamIGDBImageIcon(std::string gameName)
	{
		if (!std::filesystem::exists(std::filesystem::current_path() / ("data\\" + gameName + ".jpg")))
		{
			std::string response = requestIGDB("fields websites.*; search \\\"" + gameName + "\\\"; where version_parent = null & parent_game = null & platforms = [6];");

			std::vector<std::string> gameNameSplited;
			if (stringSplit(gameName, gameNameSplited, ' ') > 2 && (response == "" || response == "[]"))
			{
				response = requestIGDB("fields websites.*; search \\\"" + gameNameSplited[0] + ' ' + gameNameSplited[1] + "\\\"; where version_parent = null & parent_game = null & platforms = [6];");
			}

			if (response != "" && response != "[]")
			{
				std::string steamID;
				size_t startPosition = 0;
				while (true)
				{
					size_t namePosition = response.find("\"category\":", startPosition);

					if (namePosition == std::string::npos) { break; }

					size_t nameStart = namePosition + 11 + 1;
					size_t nameEnd = response.find(",", nameStart);
					startPosition = nameEnd;

					std::string category = stringTrim(response.substr(nameStart, nameEnd - nameStart));

					if (category == "13")
					{
						namePosition = response.find("\"url\":", nameEnd);
						nameStart = response.find("\"", namePosition + 6) + 1;
						nameEnd = response.find("\"", nameStart);

						steamID = stringTrim(response.substr(nameStart, nameEnd - nameStart));

						namePosition = steamID.find("app/", 0);
						nameStart = namePosition + 4;
						nameEnd = steamID.find("/", nameStart);

						steamID = stringTrim(steamID.substr(nameStart, nameEnd - nameStart));

						break;
					}
				}

				if (steamID != "")
				{
					if (!downloadFileFromUrl(std::string("data\\" + gameName + ".jpg").c_str(), "steamcdn-a.akamaihd.net",
						std::string("/steam/apps/" + steamID + "/header.jpg").c_str()))
						return;
				}
				else
				{
					response = requestIGDB("fields cover.*; search \\\"" + gameName + "\\\"; where version_parent = null & parent_game = null & platforms = [6];");

					size_t namePosition = response.find("\"image_id\":");
					size_t nameStart = response.find("\"", namePosition + 11) + 1;
					size_t nameEnd = response.find("\"", nameStart);

					std::string coverID = stringTrim(response.substr(nameStart, nameEnd - nameStart));

					if (!downloadFileFromUrl(std::string("data\\" + gameName + ".jpg").c_str(), "images.igdb.com",
						std::string("/igdb/image/upload/t_720p/" + coverID + ".jpg").c_str()))
						return;
				}
			}
		}

		image = new Image(std::string("data\\" + gameName + ".jpg").c_str());
	}

	void getBattleNetImageIcon(std::string gameName)
	{
		if (!std::filesystem::exists(std::filesystem::current_path() / ("data\\" + gameName + ".jpg")))
		{
			std::string server;
			std::string remotePath;

			if (gameName == "WoW") { server = "patchbot.io"; remotePath = "/images/games/world_of_warcraft_md.png"; }
			else if (gameName == "D3") { server = "patchbot.io"; remotePath = "/images/games/diablo_iii_md.jpg"; }
			else if (gameName == "S2") { server = "patchbot.io"; remotePath = "/images/games/starcraft_ii_md.jpg"; }
			else if (gameName == "WTCG") { server = "patchbot.io"; remotePath = "/images/games/hearthstone_md.jpg"; }
			else if (gameName == "Hero") { server = "patchbot.io"; remotePath = "/images/games/heroes_of_the_storm_md.jpg"; }
			else if (gameName == "Pro") { server = "patchbot.io"; remotePath = "/images/games/overwatch_md.jpg"; }
			else if (gameName == "S1") { server = "wp.geekout.com.ar"; remotePath = "/wp-content/uploads/2017/08/headersc.jpg"; }
			else if (gameName == "W3") { server = "gramez.com"; remotePath = "/content/uploads/2018/04/warcraft_iii_reign_of_chaos_header.jpg"; }
			else if (gameName == "ODIN") { server = "i1.wp.com"; remotePath = "/akihabarablues.com/wp-content/uploads/2016/05/header.jpg"; }
			else if (gameName == "VIPR") { server = "patchbot.io"; remotePath = "/images/games/call_of_duty_black_ops_4_md.jpg"; }
			else if (gameName == "DST2") { server = "patchbot.io"; remotePath = "/images/games/destiny_2_md.png"; }

			if (!downloadFileFromUrl(std::string("data\\" + gameName + ".jpg").c_str(), server.c_str(), remotePath.c_str()))
				return;
		}
		
		image = new Image(std::string("data\\" + gameName + ".jpg").c_str());
	}

	void getIGDBImageIcon(std::string gameName)
	{
		if (!std::filesystem::exists(std::filesystem::current_path() / ("data\\" + gameName + "_C.jpg")))
		{
			std::string response = requestIGDB("fields cover.*; search \\\"" + gameName + "\\\"; where version_parent = null & parent_game = null & platforms = [6];");
		
			std::vector<std::string> gameNameSplited;
			if (stringSplit(gameName, gameNameSplited, ' ') > 2 && (response == "" || response == "[]"))
			{
				response = requestIGDB("fields cover.*; search \\\"" + gameNameSplited[0] + ' ' + gameNameSplited[1] + "\\\"; where version_parent = null & parent_game = null & platforms = [6];");
			}

			if (response != "" && response != "[]")
			{
				size_t namePosition = response.find("\"image_id\":", 0);

				if (namePosition == std::string::npos) { return; }

				size_t nameStart = response.find("\"", namePosition + 10) + 1;
				size_t nameEnd = response.find("\"", nameStart);

				std::string coverName = stringTrim(response.substr(nameStart, nameEnd - nameStart));

				if (!downloadFileFromUrl(std::string("data\\" + gameName + "_C.jpg").c_str(), "images.igdb.com", 
					std::string("/igdb/image/upload/t_cover_big/" + coverName + ".jpg").c_str()))
					return;
			}
		}

		image = new Image(std::string("data\\" + gameName + "_C.jpg").c_str());
	}

	void loadCover(short coverOrientation)
	{
		if (image != NULL && image->getTextureId() != 0)
			image->deleteTexture();

		switch (platform)
		{
		case Steam:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getSteamImageIcon(path);
			break;
		case BattleNet:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getBattleNetImageIcon(path);
			break;
		case Custom:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getSteamIGDBImageIcon(name);
			break;
		case GOG:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getSteamIGDBImageIcon(name);
			break;
		case Origin:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getSteamIGDBImageIcon(name);
			break;
		case LOL:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getLOLImageIcon();
			break;
		case EpicGames:
			if (coverOrientation == 1)
				getIGDBImageIcon(name);
			else
				getSteamIGDBImageIcon(name);
			break;
		default:
			break;
		}
	}

public:
	Game(std::string name, Platform platform, std::string steamID, std::string launcherPath) :
		name(name), platform(platform), image(0)
	{
		switch (platform)
		{
		case Steam:
			path = steamID;
			break;
		case BattleNet:
			path = launcherPath;
			break;
		case Custom:
			path = launcherPath;
			break;
		case GOG:
			path = launcherPath;
			break;
		case Origin:
			path = launcherPath;
			break;
		case LOL:
			path = launcherPath;
			break;
		case EpicGames:
			path = launcherPath;
			break;
		default:
			break;
		}
	}

	void changeCover(short coverOrientation)
	{
		loadCover(coverOrientation);
	}

	void loadTexture() 
	{ 
		image->loadTexture(); 
	}

	inline std::string getName() { return name;	}
	inline unsigned int getCover() { return image->getTextureId(); }
	inline Platform getPlatform() { return platform; }

	bool Launch()
	{
		bool needClientRunning = false;
		std::string clientProcessName;
		std::string clientPath;

		std::string finalPath;
		std::string pathArguments;
		std::string executionPath;

		switch (platform)
		{
		case Steam:
			needClientRunning = true;
			clientProcessName = "Steam.exe";
			clientPath = finalPath = steamInstallationPath;
			pathArguments = "steam://rungameid/" + path;	
			break;
		case BattleNet:
			needClientRunning = true;
			clientProcessName = "Battle.net.exe";
			clientPath = finalPath = battleNetInstallationPath;
			pathArguments = battleNetInstallationPath + " --exec=\"launch " + path + "\"";
			break;
		case Custom:
			finalPath = path;
			break;
		case GOG:
			//needClientRunning = true;
			clientProcessName = "GalaxyClient.exe";
			clientPath = gogInstallationPath;
			finalPath = path;
			executionPath = path.substr(0, path.find_last_of('\\'));
			break;
		case Origin:
			needClientRunning = true;
			clientProcessName = "Origin.exe";
			clientPath = finalPath = originInstallationPath;
			pathArguments = "origin://launchgame/" + path;
			break;
		case LOL:
			finalPath = path;
			break;
		case EpicGames:
			finalPath = path;
			executionPath = path.substr(0, path.find_last_of('\\'));
			break;
		default:
			return false;
			break;
		}

		// Checks if client is running
		if (needClientRunning)
		{
			bool isRunning = false;
			PROCESSENTRY32 entry;
			entry.dwSize = sizeof(PROCESSENTRY32);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

			if (Process32First(snapshot, &entry))
			{
				while (Process32Next(snapshot, &entry))
				{
					if (std::string(entry.szExeFile) == clientProcessName)
					{
						isRunning = true;
						break;
					}
				}
			}

			CloseHandle(snapshot);

			if (!isRunning)
			{
				STARTUPINFO startupInfo;
				PROCESS_INFORMATION processInfo;

				ZeroMemory(&startupInfo, sizeof(startupInfo));
				startupInfo.cb = sizeof(startupInfo);
				ZeroMemory(&processInfo, sizeof(processInfo));

				int success = CreateProcess(clientPath.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

				if (success != 0)
					Sleep(10000);

				CloseHandle(processInfo.hProcess);
				CloseHandle(processInfo.hThread);
			} else {
				Sleep(1000);
			}
		}

		// Execute game process
		int success = 0;

		STARTUPINFO startupInfo;
		PROCESS_INFORMATION processInfo;
		LPSTR arguments = NULL; 
		LPCSTR currentPath = executionPath.length() > 0 ? executionPath.c_str() : NULL;

		ZeroMemory(&startupInfo, sizeof(startupInfo));
		startupInfo.cb = sizeof(startupInfo);
		ZeroMemory(&processInfo, sizeof(processInfo));

		if (pathArguments.length() > 0)
		{
			arguments = new char[pathArguments.length() + 1];
			pathArguments.copy(arguments, pathArguments.length() + 1);
			arguments[pathArguments.length()] = '\0';
		}

		success = CreateProcess(finalPath.c_str(), arguments, NULL, NULL, FALSE, 0, NULL, currentPath, &startupInfo, &processInfo);

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
			gameRunning = true;
			Sleep(3000);
			gameRunning = false;
		}
#endif

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		if (success != 0)
			return true;

		return false;
	}
};

bool Game::gameRunning = false;