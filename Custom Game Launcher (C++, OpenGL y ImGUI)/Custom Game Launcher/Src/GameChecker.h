#pragma once

#include "Game.h"

#include <set>

std::vector<Game> checkGamesInstalled()
{
	bool steam = false, battlenet = false, epic = false, uplay = false, origin = false, gog = false, glyph = false, lol = false;

	if (!std::filesystem::exists(std::filesystem::current_path() / "data"))
		std::filesystem::create_directory(std::filesystem::current_path() / "data");

	// Search for Game Clients Installed	
	for (std::string value : getInstalledPrograms())
	{
		if (value.find("Steam")						!= std::string::npos)
			steam = true;
		else if (value.find("Battle.net")			!= std::string::npos)
			battlenet = true;
		else if (value.find("Epic Games")			!= std::string::npos)
			epic = true;
		else if (value.find("Uplay")				!= std::string::npos)
			uplay = true;
		else if (value.find("Origin")				!= std::string::npos)
			origin = true;
		else if (value.find("GOG Galaxy")			!= std::string::npos)
			gog = true;
		else if (value.find("Glyph")				!= std::string::npos)
			glyph = true;
		else if (value.find("League of Legends")	!= std::string::npos)
			lol = true;
	}

	// Search for games from the Clients
	std::vector<Game> games;

	// Search for League of Legends
	if (lol)
	{
		games.emplace_back(std::string("League of Legends"), Game::LOL, "", 
			getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Riot Games, Inc\\League of Legends", "Location")
			+ "\\LeagueClient.exe");
	}

	// Search for Steam Games
	if (steam)
	{
		std::string steamPath = getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve\\Steam", "InstallPath");
		steamInstallationPath = steamPath + "\\steam.exe";

		if (steamInstallationPath != "")
		{
			std::filesystem::path steamGamesPath(steamPath + "\\steamapps");
			std::vector<std::filesystem::path> steamGamesLibraryPaths;
			steamGamesLibraryPaths.emplace_back(steamGamesPath);

			if (std::filesystem::exists(steamGamesPath))
			{
				for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(steamGamesPath))
				{
					if (entry.is_regular_file() && entry.path().has_extension() && entry.path().extension() == ".vdf")
					{
						std::ifstream inFile(entry.path().string(), std::ifstream::in);

						if (inFile.is_open())
						{
							std::string content((std::istreambuf_iterator<char>(inFile)),
								(std::istreambuf_iterator<char>()));

							for (int i = 1; i <= 10; i++)
							{
								size_t namePosition = content.find("\"" + std::to_string(i) + "\"");

								if (namePosition == std::string::npos) break;

								size_t nameStart = content.find("\"", namePosition + std::to_string(i).length() + 2) + 1;
								size_t nameEnd = content.find("\"", nameStart);

								steamGamesLibraryPaths.emplace_back(std::filesystem::path(content.substr(nameStart, nameEnd - nameStart) + "\\steamapps"));
							}

							inFile.close();
						}
					}
				}

				for (std::filesystem::path path : steamGamesLibraryPaths)
				{
					for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
					{
						if (entry.is_regular_file() && entry.path().has_extension() &&
							entry.path().extension() == ".acf" && entry.path().filename().string() != "appmanifest_228980.acf")
						{
							std::ifstream inFile(entry.path().string(), std::ifstream::in);

							if (inFile.is_open())
							{
								std::string content((std::istreambuf_iterator<char>(inFile)),
									(std::istreambuf_iterator<char>()));

								std::string gameName;
								std::string steamId;
								{
									size_t namePosition = content.find("\"name\"");
									size_t nameStart = content.find("\"", namePosition + 6) + 1;
									size_t nameEnd = content.find("\"", nameStart);

									gameName = content.substr(nameStart, nameEnd - nameStart);
								}
								{
									size_t namePosition = content.find("\"appid\"");
									size_t nameStart = content.find("\"", namePosition + 7) + 1;
									size_t nameEnd = content.find("\"", nameStart);

									steamId = stringTrim(content.substr(nameStart, nameEnd - nameStart));
								}

								games.emplace_back(gameName, Game::Steam, steamId, "");

								inFile.close();
							}
						}
					}
				}
			}
		}
	}

	// Search for Custom Games
	std::filesystem::path customGamesPath("C:\\Games");
	if (std::filesystem::exists(customGamesPath))
	{
		for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(customGamesPath))
		{
			std::string gameLauncher;
			std::string gameLauncher2;
			std::string gameLauncher3;
			std::string steamId;

			std::vector<std::string> gameNameParts;
			std::string folderName = entry.path().filename().string();
			std::transform(folderName.begin(), folderName.end(), folderName.begin(), ::tolower);
			stringSplit(folderName, gameNameParts, ' ');

			if (gameNameParts.size() == 0) break;

			std::string gameAcronym;

			for (std::string part : gameNameParts)
			{
				gameAcronym += part[0];
			}

			for (const std::filesystem::directory_entry recursiveEntry : std::filesystem::recursive_directory_iterator(entry))
			{
				std::string filename = recursiveEntry.path().filename().string();
				std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

				if (recursiveEntry.is_regular_file() && recursiveEntry.path().has_extension() && 
					recursiveEntry.path().extension() == ".ini" &&
					(filename.find("steam") != std::string::npos || filename.find("valve") != std::string::npos))
				{
					std::ifstream inFile(recursiveEntry.path().string(), std::ifstream::in);

					if (inFile.is_open())
					{
						std::string content((std::istreambuf_iterator<char>(inFile)),
							(std::istreambuf_iterator<char>()));

						{
							size_t namePosition = content.find("AppId");
							size_t nameStart = content.find("=", namePosition + 5) + 1;
							size_t nameEnd = content.find("\n", nameStart);

							steamId = stringTrim(content.substr(nameStart, nameEnd - nameStart));
						}

						inFile.close();
					}
				}
				else if (recursiveEntry.is_regular_file() && recursiveEntry.path().has_extension() &&
					recursiveEntry.path().extension() == ".exe" && (filename.find(gameNameParts[0]) != std::string::npos ||
					(gameNameParts.size() > 1 && filename.find(gameNameParts[1]) != std::string::npos) ||
					(gameNameParts.size() > 2 && filename.find(gameNameParts[2]) != std::string::npos)))
				{
					gameLauncher = recursiveEntry.path().string();
				}

				if (recursiveEntry.is_regular_file() && recursiveEntry.path().has_extension() &&
					recursiveEntry.path().extension() == ".exe" && filename.find("launcher") != std::string::npos)
				{
					gameLauncher2 = recursiveEntry.path().string();
				} 
				else if (recursiveEntry.is_regular_file() && recursiveEntry.path().has_extension() &&
					recursiveEntry.path().extension() == ".exe" && filename.find(gameAcronym) != std::string::npos)
				{
					gameLauncher3 = recursiveEntry.path().string();
				}
			}

			if(gameLauncher != "")
				games.emplace_back(folderName, Game::Custom, steamId, gameLauncher);
			else if(gameLauncher3 != "")
				games.emplace_back(folderName, Game::Custom, steamId, gameLauncher3);
			else 
				games.emplace_back(folderName, Game::Custom, steamId, gameLauncher2);
		}
	}

	// Search for Battle Net Games
	if (battlenet)
	{
		battleNetInstallationPath = getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Battle.net", "DisplayIcon");

		bool wow = false, diablo3 = false, starcraft2 = false, heartstone = false, heroes = false, overwatch = false, starcraft = false, warcraft3 = false, codmw = false, codbo4 = false, destiny2 = false;

		for (std::string value : getInstalledPrograms())
		{
			if (value.find("World of Warcraft")			!= std::string::npos)
				wow = true;
			else if (value.find("Diablo III")			!= std::string::npos)
				diablo3 = true;
			else if (value.find("StarCraft II")			!= std::string::npos)
				starcraft2 = true;
			else if (value.find("Hearthstone")			!= std::string::npos)
				heartstone = true;
			else if (value.find("Heroes of the Storm")	!= std::string::npos)
				heroes = true;
			else if (value.find("Overwatch")			!= std::string::npos)
				overwatch = true;
			else if (value.find("StarCraft")			!= std::string::npos)
				starcraft = true;
			else if (value.find("Warcraft III")			!= std::string::npos)
				warcraft3 = true;
			else if (value.find("Call of Duty: MW")		!= std::string::npos)
				codmw = true;
			else if (value.find("Call of Duty: BO4")	!= std::string::npos)
				codbo4 = true;
			else if (value.find("Destiny 2")			!= std::string::npos)
				destiny2 = true;
		}

		if (wow)		games.emplace_back("World of Warcraft", Game::BattleNet, "", "WoW");
		if (diablo3)	games.emplace_back("Diablo III",		Game::BattleNet, "", "D3");
		if (starcraft2) games.emplace_back("StarCraft II",		Game::BattleNet, "", "S2");
		if (heartstone) games.emplace_back("Hearthstone",		Game::BattleNet, "", "WTCG");
		if (heroes)		games.emplace_back("Heroes of Storm",	Game::BattleNet, "", "Hero");
		if (overwatch)	games.emplace_back("Overwatch",			Game::BattleNet, "", "Pro");
		if (starcraft)	games.emplace_back("StarCraft",			Game::BattleNet, "", "S1");
		if (warcraft3)	games.emplace_back("Warcraft III",		Game::BattleNet, "", "W3");
		if (codmw)		games.emplace_back("Call of Duty: MW",	Game::BattleNet, "", "ODIN");
		if (codbo4)		games.emplace_back("Call of Duty: BO4", Game::BattleNet, "", "VIPR");
		if (destiny2)	games.emplace_back("Destiny 2",			Game::BattleNet, "", "DST2");
	}

	// Search for GOG Galaxy Games
	if (gog)
	{
		gogInstallationPath = getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\GOG.com\\GalaxyClient\\paths", "client")
			+ "\\" + getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\GOG.com\\GalaxyClient", "clientExecutable");
		
		std::vector<std::vector<std::string>> values = getRegisterMultipleSubKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\GOG.com\\Games", { "gameName", "launchCommand" });

		for (std::vector<std::string> value : values)
		{
			games.emplace_back(value[0], Game::GOG, "", value[1]);
		}
	}

	// Search for Origin Games
	if (origin)
	{
		originInstallationPath = getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Origin", "ClientPath");

		std::filesystem::path orginContentPath("C:\\ProgramData\\Origin\\LocalContent");

		if (std::filesystem::exists(orginContentPath))
		{
			for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(orginContentPath))
			{
				if (entry.is_directory()) 
				{
					for (const std::filesystem::directory_entry subEntry : std::filesystem::directory_iterator(entry))
					{
						if (subEntry.is_regular_file() && subEntry.path().has_extension() && subEntry.path().extension() == ".mfst")
						{
							std::ifstream inFile(subEntry.path().string(), std::ifstream::in);

							if (inFile.is_open())
							{
								std::string content((std::istreambuf_iterator<char>(inFile)),
									(std::istreambuf_iterator<char>()));

								std::string originId;
								{
									size_t namePosition = content.find("&id=");
									size_t nameStart = namePosition + 4;
									size_t nameEnd = content.find("&", nameStart);

									originId = content.substr(nameStart, nameEnd - nameStart);
								}

								games.emplace_back(entry.path().filename().string(), Game::Origin, "", stringUrlDecode(originId.c_str()));

								inFile.close();
							}
						}
					}
				}
			}
		}
	}

	// Search for Epic Games games
	if (epic)
	{
		std::filesystem::path epicContentPath(getRegisterKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Epic Games\\EpicGamesLauncher", "AppDataPath") + "Manifests");

		if (std::filesystem::exists(epicContentPath))
		{
			for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(epicContentPath))
			{
				if (entry.is_regular_file() && entry.path().has_extension() && entry.path().extension() == ".item")
				{
					std::ifstream inFile(entry.path().string(), std::ifstream::in);

					if (inFile.is_open())
					{
						std::string content((std::istreambuf_iterator<char>(inFile)),
							(std::istreambuf_iterator<char>()));

						std::string gameName;
						{
							size_t namePosition = content.find("\"DisplayName\"");
							size_t nameStart = namePosition + 16;
							size_t nameEnd = content.find("\"", nameStart);

							gameName = content.substr(nameStart, nameEnd - nameStart);
						}
						std::string gamePath;
						{
							size_t namePosition = content.find("\"InstallLocation\"");
							size_t nameStart = namePosition + 20;
							size_t nameEnd = content.find("\"", nameStart);

							gamePath = content.substr(nameStart, nameEnd - nameStart);
						}
						{
							size_t namePosition = content.find("\"LaunchExecutable\"");
							size_t nameStart = namePosition + 21;
							size_t nameEnd = content.find("\"", nameStart);

							gamePath += "\\" + content.substr(nameStart, nameEnd - nameStart);
						}

						games.emplace_back(gameName, Game::EpicGames, "", gamePath);

						inFile.close();
					}
				}
			}
		}
	}

	return games;
}