#pragma once

#include "Launcher.h"

#include <set>

std::vector<Launcher> checkLaunchersInstalled()
{
	bool steam = false, battlenet = false, epic = false, uplay = false, origin = false, gog = false, glyph = false, lol = false;

	// Search for Game Clients Installed	
	for (std::string value : getInstalledPrograms())
	{
		if (value.find("Steam") != std::string::npos)
			steam = true;
		else if (value.find("Battle.net") != std::string::npos)
			battlenet = true;
		else if (value.find("Epic Games") != std::string::npos)
			epic = true;
		else if (value.find("Uplay") != std::string::npos)
			uplay = true;
		else if (value.find("Origin") != std::string::npos)
			origin = true;
		else if (value.find("GOG Galaxy") != std::string::npos)
			gog = true;
		else if (value.find("Glyph") != std::string::npos)
			glyph = true;
		else if (value.find("League of Legends") != std::string::npos)
			lol = true;
	}

	// Search for games from the Clients
	std::vector<Launcher> launchers;

	// Search for League of Legends
	if (lol)
	{
		launchers.emplace_back(std::string("League of Legends"), Launcher::LOL,
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Riot Games, Inc\\League of Legends", "Location")
			+ "\\LeagueClient.exe");
	}

	// Search for Steam Games
	if (steam)
	{
		launchers.emplace_back(std::string("Steam"), Launcher::Steam,
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve\\Steam", "InstallPath")
			+ "\\steam.exe");

	}

	// Search for Battle Net Games
	if (battlenet)
	{
		launchers.emplace_back(std::string("Battle Net"), Launcher::BattleNet,
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Battle.net", "DisplayIcon"));
	}

	// Search for GOG Galaxy Games
	if (gog)
	{
		launchers.emplace_back(std::string("GOG Galaxy"), Launcher::GOG,
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\GOG.com\\GalaxyClient\\paths", "client")
			+ "\\" + getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\GOG.com\\GalaxyClient", "clientExecutable"));
	}

	// Search for Origin Games
	if (origin)
	{
		launchers.emplace_back(std::string("Origin"), Launcher::Origin,
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Origin", "ClientPath"));
	}

	// Search for Epic Games games
	if (epic)
	{
		std::string epicPath = getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\EpicGames\\Unreal Engine", "InstallDir");

		for (const std::filesystem::directory_entry recursiveEntry : std::filesystem::recursive_directory_iterator(epicPath)) {
			if (recursiveEntry.path().filename() == "EpicGamesLauncher.exe")
			{
				launchers.emplace_back(std::string("Epic Games"), Launcher::EpicGames, recursiveEntry.path().string());
				break;
			}
		}
	}

	return launchers;
}