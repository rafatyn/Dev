#define NOMINMAX
#define COVERTYPE 0
#define BLOCK_START 0

#include "Dependencies\imgui\imgui.h"
#include "Dependencies\imgui\imgui_impl_glfw.h"
#include "Dependencies\imgui\imgui_impl_opengl3.h"
#include "Dependencies\ImGuiNewWidgets.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <thread>

#include "Src\Window.h"
#include "Src\GameChecker.h"
#include "Src\AppChecker.h"
#include "Src\LauncherChecker.h"
#include "Src\Utils.h"
#include "Src\AppSettings.h"


int main(int, char**)
{
	// Close console on Release
#ifndef _DEBUG
	FreeConsole();
#endif

	// Create window
	Window windowHandler;

	// App settings
	AppSettings appSettings(COVERTYPE);

	// Multithread mutex
	bool loadingGames = false;
	bool gamesCoverLoaded = false;
	bool loadingLaunchers = false;
	bool launchersCoverLoaded = false;

	// Load title bar icons
	Image spotifyIcon		= Image(std::string("icons\\spotify_icon2.png").c_str());	spotifyIcon.loadTexture();
	Image discordIcon		= Image(std::string("icons\\discord_icon2.png").c_str());	discordIcon.loadTexture();
	Image coverMode0Icon	= Image(std::string("icons\\layout_icon1.png").c_str());	coverMode0Icon.loadTexture();
	Image coverMode1Icon	= Image(std::string("icons\\layout_icon1.png").c_str());	coverMode1Icon.loadTexture();
	Image coverMode2Icon	= Image(std::string("icons\\layout_icon2.png").c_str());	coverMode2Icon.loadTexture();
	Image minimizeIcon		= Image(std::string("icons\\minimize_icon2.png").c_str());	minimizeIcon.loadTexture();
	Image maximizeIcon		= Image(std::string("icons\\maximize_icon2.png").c_str());	maximizeIcon.loadTexture();
	Image restoreIcon		= Image(std::string("icons\\restore_icon2.png").c_str());	restoreIcon.loadTexture();
	Image closeIcon			= Image(std::string("icons\\x_close_icon2.png").c_str());	closeIcon.loadTexture();

	// Title bar sizes
	const float titleHeight = 45.0f;
	const float iconScale = 1.7f;
	const float layoutIconScale = 1.2f;
	const float titleBarIcons = (titleHeight * iconScale * 3) + (titleHeight * layoutIconScale * 5) + 80.0f;
	bool isDragging = false;
	
	// Load fonts
	ImGuiIO& io = ImGui::GetIO();
	//ImFont* titleFont = io.Fonts->AddFontFromFileTTF("fonts/AllertaStencil-Regular.ttf", titleHeight);
	ImFont* titleFont = io.Fonts->AddFontFromFileTTF("fonts/Monoton-Regular.ttf", titleHeight);

	// Tabs
	std::vector<std::string> tabs = { "Games", "Favorites", "Launchers" };
	int tabIndex = 0;

	// Context menu
	bool showContextMenu = false;
	std::string contextMenuParent;
	ImVec2 contextMenuPos;


	// Load games
	std::vector<Game> games;

	auto gameLoader = [&]() {
		loadingGames = true;
		gamesCoverLoaded = false;
		games = checkGamesInstalled();
		for (int i = 0; i < games.size(); i++) {
			games[i].changeCover(appSettings.getGameCoverOrientation());
		}
		loadingGames = false;
	};
	std::thread* gameLoaderThread = new std::thread(gameLoader);


	// Load apps
	std::vector<App> apps;

	auto appLoader = [&]() {
		apps = checkAppsInstalled();
	};
	std::thread* appLoaderThread = new std::thread(appLoader);


	// Load launchers
	std::vector<Launcher> launchers;

	auto launcherLoader = [&]() {
		loadingLaunchers = true;
		launchers = checkLaunchersInstalled();
		loadingLaunchers = false;
	};
	std::thread* launcherLoaderThread = new std::thread(launcherLoader);

	// ------------------------------------------------------------------ //	

    // Main loop
    while (!windowHandler.windowWillClose())
    {
		windowHandler.startFrame();

		//-----------------------------------------------------//

		int winWidth, winHeight;
		winWidth = windowHandler.getWindowSize().x;
		winHeight = windowHandler.getWindowSize().y;

		//-----------------------------------------------------//
		
		// Title bar window
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.12f, 0.13f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.12f, 0.13f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.29f, 0.32f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(winWidth, titleHeight));
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			ImGui::Begin("Title", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

			// Maximize window when double click over title bar
			if (ImGui::IsMouseDoubleClicked(0))
			{
				if (ImGui::GetMousePos().y <= titleHeight && ImGui::GetMousePos().x < winWidth - titleBarIcons) {
					windowHandler.toggleMaximizeWindow();
				}
			}

			// Move window when dragging over title bar
			if (ImGui::IsMouseDragging(0))
			{
				if (ImGui::GetMousePos().y <= titleHeight && ImGui::GetMousePos().x < winWidth - titleBarIcons && !isDragging) {
					isDragging = true;
				}
			}
			else if (isDragging) {
				isDragging = false;
			}

			if (isDragging)
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
				windowHandler.moveWindowDragged();
			}

			// TODO: Implement resize

			// Window title
			ImGui::SameLine(15.0f, 0.0f);
			ImGui::PushFont(titleFont);
			ImGui::Text("Game collection");
			ImGui::PopFont();
			ImGui::SameLine(winWidth - titleBarIcons, 0.0f);

			// App icons
			if (ImGui::ImageButton((ImTextureID)spotifyIcon.getTextureId(), ImVec2(titleHeight * layoutIconScale, titleHeight), ImVec2(-0.1f, -0.1f), ImVec2(1.1f, 1.1f), 0)) {
				apps[0].Launch();
			}
			ImGui::SameLine(0.0f, 0.0f);

			if (ImGui::ImageButton((ImTextureID)discordIcon.getTextureId(), ImVec2(titleHeight * layoutIconScale, titleHeight), ImVec2(0.0f, -0.1f), ImVec2(1.0f, 1.1f), 0)) {
				apps[1].Launch();
			}

			ImGui::SameLine(0.0f, 20.0f);
			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
			ImGui::SameLine(0.0f, 20.0f);

			// Layout icons
			if (ImGui::ImageButton((ImTextureID)coverMode0Icon.getTextureId(), ImVec2(titleHeight * layoutIconScale, titleHeight), ImVec2(0.0f, -0.2f), ImVec2(1.0f, 1.2f), 0)) {
				appSettings.changeCoverType(0);
				auto layoutLoader = [&]() {
					loadingGames = true;
					gamesCoverLoaded = false;
					for (int i = 0; i < games.size(); i++) {
						games[i].changeCover(appSettings.getGameCoverOrientation());
					}
					loadingGames = false;
				};
				std::thread* layoutLoaderThread = new std::thread(layoutLoader);
			}
			ImGui::SameLine(0.0f, 0.0f);

			if (ImGui::ImageButton((ImTextureID)coverMode1Icon.getTextureId(), ImVec2(titleHeight * layoutIconScale, titleHeight), ImVec2(-0.15f, 0.0f), ImVec2(1.15f, 1.0f), 0)) {
				appSettings.changeCoverType(1);
				auto layoutLoader = [&]() {
					loadingGames = true;
					gamesCoverLoaded = false;
					for (int i = 0; i < games.size(); i++) {
						games[i].changeCover(appSettings.getGameCoverOrientation());
					}
					loadingGames = false;
				};
				std::thread* layoutLoaderThread = new std::thread(layoutLoader);
			}
			ImGui::SameLine(0.0f, 0.0f);

			if (ImGui::ImageButton((ImTextureID)coverMode2Icon.getTextureId(), ImVec2(titleHeight * layoutIconScale, titleHeight), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0)) {
				appSettings.changeCoverType(2);
				auto layoutLoader = [&]() {
					loadingGames = true;
					gamesCoverLoaded = false;
					for (int i = 0; i < games.size(); i++) {
						games[i].changeCover(appSettings.getGameCoverOrientation());
					}
					loadingGames = false;
				};
				std::thread* layoutLoaderThread = new std::thread(layoutLoader);
			}

			ImGui::SameLine(0.0f, 20.0f);
			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
			ImGui::SameLine(0.0f, 20.0f);

			// Window basic icons
			if (ImGui::ImageButton((ImTextureID)minimizeIcon.getTextureId(), ImVec2(titleHeight * iconScale, titleHeight), ImVec2(0.0f, -0.2f), ImVec2(1.0f, 1.2f), 0))
				windowHandler.minimizeWindow();
			ImGui::SameLine(0.0f, 0.0f);

			if (ImGui::ImageButton((ImTextureID)(windowHandler.isMaximized() ? restoreIcon.getTextureId() : maximizeIcon.getTextureId()), ImVec2(titleHeight * iconScale, titleHeight), ImVec2(0.0f, -0.2f), ImVec2(1.0f, 1.2f), 0))
				windowHandler.toggleMaximizeWindow();

			ImGui::SameLine(0.0f, 0.0f);

			if (ImGui::ImageButton((ImTextureID)closeIcon.getTextureId(), ImVec2(titleHeight * iconScale, titleHeight), ImVec2(0.0f, -0.2f), ImVec2(1.0f, 1.2f), 0))
				windowHandler.closeWindow();

			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		//-----------------------------------------------------//
		
		// Tabs window
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(winWidth, titleHeight));
			ImGui::SetNextWindowPos(ImVec2(0.0f, titleHeight));
			ImGui::Begin("Tabs", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.45f, 0.45f, 0.45f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
			for (int i = 0; i < tabs.size(); i++)
			{
				bool tabSelected = false;
				if (tabIndex == i)
					tabSelected = true;

				if (tabSelected)
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

				if (ImGui::Button(tabs[i].c_str(), ImVec2(winWidth / 3, titleHeight)))
				{
					tabIndex = i;
				}

				if (tabSelected)
					ImGui::PopStyleColor();

				ImGui::SameLine(0.0f, 0.0f);
			}
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

			ImGui::End();
			ImGui::PopStyleVar();
		}

		//-----------------------------------------------------//

		// Games tab
		if (tabIndex == 0)
		{
			ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove;

			if (loadingGames)
				windowFlags |= ImGuiWindowFlags_NoInputs;

			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(winWidth, winHeight - titleHeight * 2));
			ImGui::SetNextWindowPos(ImVec2(0.0f, titleHeight * 2));
			ImGui::Begin("Games tab", 0, windowFlags);

			if (!loadingGames) // && !isDragging
			{
				if (!gamesCoverLoaded) {
					for (Game game : games)
					{
						game.loadTexture();
					}
					gamesCoverLoaded = true;
				}

				ImGui::NoSpaceNewLine();
				ImGui::VerticalDummy(appSettings.getGameInitialVerticalMargin());
				ImGui::NoSpaceNewLine();

				unsigned int gamesPerLine = 0;
				unsigned int maxGamesPerLine;

				float remainSpace = winWidth - (winWidth * appSettings.getGameInitialHorizontalMargin() * 2);
				float scaledCoverMinSize = (appSettings.getGameCoverMinSize() * windowHandler.getWindowScale().x);
				maxGamesPerLine = remainSpace / (scaledCoverMinSize + (winWidth * appSettings.getGameCoverMargin()));

				float gameWidth;
				if (maxGamesPerLine > games.size()) {
					maxGamesPerLine = games.size() + 1;
					float temporyWinWidth = ((maxGamesPerLine * scaledCoverMinSize) / ((1 - (appSettings.getGameInitialHorizontalMargin() * 2)) - 
						(maxGamesPerLine * appSettings.getGameCoverMargin()))) - 1;

					maxGamesPerLine = games.size();
					remainSpace = temporyWinWidth - (temporyWinWidth * appSettings.getGameInitialHorizontalMargin() * 2);
					gameWidth = (remainSpace - (temporyWinWidth * appSettings.getGameCoverMargin() * (maxGamesPerLine - 1))) / maxGamesPerLine;
				}
				else
					gameWidth = (remainSpace - (winWidth * appSettings.getGameCoverMargin() * (maxGamesPerLine - 1)) - 
					((appSettings.getGameCoverBorder() != 0 ? ImGui::GetCurrentContext()->Style.FramePadding.x * 2 : 0) * maxGamesPerLine)) / maxGamesPerLine;

				for (Game game : games)
				{
					if (gamesPerLine == maxGamesPerLine) {
						ImGui::NoSpaceNewLine();
						ImGui::VerticalDummy(appSettings.getGameLineMargin());
						ImGui::NoSpaceNewLine();
						gamesPerLine = 0;
					}
					
					if (gamesPerLine == 0)
						ImGui::SameLine(winWidth * appSettings.getGameInitialHorizontalMargin(), 0.0f);
					else
						ImGui::SameLine(0, winWidth * appSettings.getGameCoverMargin());

					if ((ImTextureID)game.getCover() == 0)
					{
						ImVec2 cursorPos = ImGui::GetCursorPos();
						if (ImGui::ImageButton((ImTextureID)0, ImVec2(gameWidth, gameWidth / appSettings.getGameCoverRatio()), ImVec2(0, 0), ImVec2(1.0f, 1.0f), appSettings.getGameCoverBorder()))
						{
							int x = 0;
						}

						ImGui::SetCursorPosX(cursorPos.x + ((gameWidth - ImGui::CalcTextSize(game.getName().c_str()).x + (appSettings.getGameCoverBorder() != 0 ? ImGui::GetCurrentContext()->Style.FramePadding.x * 2 : 0)) / 2));
						ImGui::SetCursorPosY(cursorPos.y + (gameWidth / appSettings.getGameCoverRatio() / 2) - (ImGui::CalcTextSize(game.getName().c_str()).y / 2));
						ImGui::Text(game.getName().substr(0, gameWidth / (ImGui::CalcTextSize(game.getName().c_str()).x / game.getName().length())).c_str());
						ImGui::SameLine(0, (gameWidth - ImGui::CalcTextSize(game.getName().c_str()).x + (appSettings.getGameCoverBorder() != 0 ? ImGui::GetCurrentContext()->Style.FramePadding.x * 2 : 0)) / 2);
						ImGui::SetCursorPosY(cursorPos.y);
						ImGui::Dummy(ImVec2(0, 0));
					}
					else
					{
						ImVec2 zoomStart(0.0f, 0.0f);
						ImVec2 zoomEnd(1.0f, 1.0f);

						if (ImGui::ImageButtonZoomOnHover((ImTextureID)game.getCover(), ImVec2(gameWidth, gameWidth / appSettings.getGameCoverRatio()), zoomStart, zoomEnd, appSettings.getGameCoverBorder()))
						{
							Game* gamePointer = new Game(game);
							auto f = [&]() {
								gamePointer->Launch();
							};

							std::thread* thread_object = new std::thread(f);
						}

						if (ImGui::IsItemHovered())
						{
							zoomStart = ImVec2(0.05f, 0.05f);
							zoomEnd = ImVec2(0.95f, 0.95f);

							if (ImGui::IsMouseClicked(1))
							{
								showContextMenu = true;
								contextMenuParent = game.getName();
								contextMenuPos = ImGui::GetMousePos();
							}

							if (showContextMenu)
							{
								ImDrawList* drawList = ImGui::GetWindowDrawList();
								//drawList->AddText(contextMenuPos, ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 1, 1)), game.getName().c_str());
								// TODO: See Popups -> Context Menus in demo window
							}
						}
						else
						{
							if (contextMenuParent == game.getName())
								showContextMenu = false;

							zoomStart = ImVec2(0.0f, 0.0f);
							zoomEnd = ImVec2(1.0f, 1.0f);
						}
					}

					gamesPerLine++;
				}

				ImGui::NoSpaceNewLine();
				ImGui::VerticalDummy(appSettings.getGameInitialVerticalMargin());

				// Game running spinner
				if (Game::gameRunning)
				{
					ImGui::WaitingModal((std::string("Process") + "##" + std::to_string(tabIndex)).c_str(), "Game runnning");
				}
			}
			else {
				// Loading games spinner
				ImGui::LocalWaitingModal((std::string("Loading") + "##" + std::to_string(tabIndex)).c_str(), "Loading games");
			}

			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
		}

		// Favorites tab
		if (tabIndex == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(winWidth, winHeight - titleHeight * 2));
			ImGui::SetNextWindowPos(ImVec2(0.0f, titleHeight * 2));
			ImGui::Begin("Favorites tab", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove);
			
			

			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
		}

		// Launchers tab
		if (tabIndex == 2)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(winWidth, winHeight - titleHeight * 2));
			ImGui::SetNextWindowPos(ImVec2(0.0f, titleHeight * 2));
			ImGui::Begin("Launchers tab", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoMove);
			
			if (!loadingLaunchers)
			{
				if (!launchersCoverLoaded) {
					for (Launcher launcher : launchers)
					{
						launcher.loadTexture();
					}
					launchersCoverLoaded = true;
				}

				float minValue = 150.0f, maxValue = 250.0f;

				/*ImGui::NoSpaceNewLine();
				ImGui::SliderFloatCustomizable("Size", appSettings.getLauncherCoverMinSizePointer(), &minValue, &maxValue, "%.0f", 5.0f);
				ImGui::NoSpaceNewLine();*/

				ImGui::NoSpaceNewLine();
				ImGui::VerticalDummy(appSettings.getLauncherInitialVerticalMargin());
				ImGui::NoSpaceNewLine();

				unsigned int launchersPerLine = 0;
				unsigned int maxLaunchersPerLine;

				float remainSpace = winWidth - (winWidth * appSettings.getLauncherInitialHorizontalMargin() * 2);
				float scaledCoverMinSize = (appSettings.getLauncherCoverMinSize() * windowHandler.getWindowScale().x);
				maxLaunchersPerLine = remainSpace / (scaledCoverMinSize + (winWidth * appSettings.getLauncherCoverMargin()));

				float launcherWidth;
				if (maxLaunchersPerLine > launchers.size()) {
					maxLaunchersPerLine = launchers.size() + 1;
					float temporyWinWidth = ((maxLaunchersPerLine * scaledCoverMinSize) / ((1 - (appSettings.getLauncherInitialHorizontalMargin() * 2)) - 
						(maxLaunchersPerLine * appSettings.getLauncherCoverMargin()))) - 1;

					maxLaunchersPerLine = launchers.size();
					remainSpace = temporyWinWidth - (temporyWinWidth * appSettings.getLauncherInitialHorizontalMargin() * 2);
					launcherWidth = (remainSpace - (temporyWinWidth * appSettings.getLauncherCoverMargin() * (maxLaunchersPerLine - 1))) / maxLaunchersPerLine;
				}
				else
					launcherWidth = (remainSpace - (winWidth * appSettings.getLauncherCoverMargin() * (maxLaunchersPerLine - 1))) / maxLaunchersPerLine;

				for (Launcher launcher : launchers)
				{
					if (launchersPerLine == maxLaunchersPerLine) {
						ImGui::NoSpaceNewLine();
						ImGui::VerticalDummy(appSettings.getLauncherLineMargin());
						ImGui::NoSpaceNewLine();
						launchersPerLine = 0;
					}

					if (launchersPerLine == 0)
						ImGui::SameLine(winWidth * appSettings.getLauncherInitialHorizontalMargin(), 0.0f);
					else
						ImGui::SameLine(0, winWidth * appSettings.getLauncherCoverMargin());

					if ((ImTextureID)launcher.getCover() != 0)
					{
						ImVec2 zoomStart(0.0f, 0.0f);
						ImVec2 zoomEnd(1.0f, 1.0f);

						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 0.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 0.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 0.0f));
						if (ImGui::ImageButtonZoomOnHover((ImTextureID)launcher.getCover(), ImVec2(launcherWidth, launcherWidth), zoomStart, zoomEnd, 0))
						{
							Launcher* launcherPointer = new Launcher(launcher);
							auto f = [&]() {
								launcherPointer->Launch();
							};

							std::thread* thread_object = new std::thread(f);
						}
						ImGui::PopStyleColor();
						ImGui::PopStyleColor();
						ImGui::PopStyleColor();

						if (ImGui::IsItemHovered())
						{
							zoomStart = ImVec2(0.05f, 0.05f);
							zoomEnd = ImVec2(0.95f, 0.95f);
						}
						else
						{
							zoomStart = ImVec2(0.0f, 0.0f);
							zoomEnd = ImVec2(1.0f, 1.0f);
						}
					}

					launchersPerLine++;
				}

				ImGui::NoSpaceNewLine();
				ImGui::VerticalDummy(appSettings.getLauncherInitialVerticalMargin());

				// Game running spinner
				if (Launcher::launcherRunning)
				{
					ImGui::WaitingModal((std::string("Process") + "##" + std::to_string(tabIndex)).c_str(), "Launcher runnning");
				}
			}
			else {
				// Loading launchers spinner
				ImGui::LocalWaitingModal((std::string("Loading") + "##" + std::to_string(tabIndex)).c_str(), "Loading launchers");
			}


			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
		}

		//-----------------------------------------------------//

		//ImGui::ShowDemoWindow();

		//-----------------------------------------------------//

        // Rendering
		windowHandler.renderFrame();
    }

    // Cleanup   
	spotifyIcon.deleteTexture();
	discordIcon.deleteTexture();
	coverMode0Icon.deleteTexture();
	coverMode1Icon.deleteTexture();
	coverMode2Icon.deleteTexture();
	minimizeIcon.deleteTexture();
	maximizeIcon.deleteTexture();
	restoreIcon.deleteTexture();
	closeIcon.deleteTexture();

    return 0;
}