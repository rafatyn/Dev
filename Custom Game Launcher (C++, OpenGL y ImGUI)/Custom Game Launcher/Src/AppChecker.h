#pragma once

#include <filesystem>

#include "App.h"

std::vector<App> checkAppsInstalled()
{
	std::vector<App> apps;

	// Search for Apps Installed
	std::string spotifyPath = getRegisterKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Spotify", "InstallLocation");
	std::string discordPath = getRegisterKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Discord", "InstallLocation");
	
	if (spotifyPath != "")
	{
		for (const std::filesystem::directory_entry recursiveEntry : std::filesystem::recursive_directory_iterator(spotifyPath)) {
			if (recursiveEntry.path().filename() == "Spotify.exe")
			{
				apps.emplace_back(std::string("Spotify"), App::Spotify, recursiveEntry.path().string());
				break;
			}
		}
	}

	if (discordPath != "") {
		for (const std::filesystem::directory_entry recursiveEntry : std::filesystem::recursive_directory_iterator(discordPath)) {
			if (recursiveEntry.path().filename() == "Discord.exe")
			{
				apps.emplace_back(std::string("Discord"), App::Discord, recursiveEntry.path().string());
				break;
			}
		}
	}

	return apps;
}
