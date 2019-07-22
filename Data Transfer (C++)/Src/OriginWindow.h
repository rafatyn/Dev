#pragma once

#include <string>
#include <filesystem>

class OriginDirectoryWindow
{
public:
	enum WindowPosition { Left, TopLeft, BottomLeft };

private:
	char* currentPathChar;
	std::filesystem::path currentPath;
	std::vector<std::pair<std::string, bool>> childs;

	const char* windowName;
	int posX, posY, width, height, winWidth, winHeight;
	WindowPosition windowPosition;

	void loadLists()
	{
		childs.resize(0);

		for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(currentPath))
		{
			childs.emplace_back(entry.path().filename().string(), false);
		}
	}

	void loadPositionAndSize(WindowPosition position)
	{
		windowPosition = position;

        const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
        float fontSize = monitor->width / 100.0f;
        float framePadding = ImGui::GetStyle().FramePadding.y;
        int padding = round(fontSize + framePadding);

		switch (position)
		{
		case Left:
			posX = 0; posY = padding;
			width = winWidth / 2; height = winHeight - (padding);
			break;
		case TopLeft:
			posX = 0; posY = padding;
			width = winWidth / 2; height = (winHeight - padding) / 2;
			break;
		case BottomLeft:
			posX = 0; posY = padding + ((winHeight - padding) / 2);
			width = winWidth / 2; height = (winHeight - padding) / 2;
			break;
		}
	}

public:
	OriginDirectoryWindow(const char* name, GLFWwindow* window, WindowPosition position, std::string path = "")
	{
		windowName = name;

		if(path != "")
			updatePath(path);
		else
			updatePath(std::filesystem::current_path().string());

		glfwGetWindowSize(window, &winWidth, &winHeight);
		loadPositionAndSize(position);
	}

	bool updatePath(std::string path)
	{
		if (currentPath.string() != path)
		{
			std::filesystem::path dirPath(path);

			if (std::filesystem::exists(dirPath)) {
				currentPath = dirPath;

				currentPathChar = new char[path.size() + 1];
				std::copy(path.begin(), path.end(), currentPathChar);
				currentPathChar[path.size()] = '\0';
				
				loadLists();
				return true;
			}

			return false;
		}
		else 
		{
			return true;
		}
	}

	void updateWindowSize(GLFWwindow* window)
	{
		glfwGetWindowSize(window, &winWidth, &winHeight);
		loadPositionAndSize(windowPosition);
	}

	void updatePosition(WindowPosition position)
	{
		loadPositionAndSize(position);
	}

	std::vector<std::pair<std::string, bool>>* getChildController()
	{
		return &childs;
	}

	std::vector<std::string> getSelectedChilds()
	{
		std::vector<std::string> selectedChilds;

		for (std::pair<std::string, bool> child : childs)
		{
			if (child.second)
				selectedChilds.emplace_back(child.first);
		}

		return selectedChilds;
	}

	std::string getCurrentPath()
	{
		return currentPath.string();
	}

	void show()
	{		
		ImGui::SetNextWindowPos(ImVec2(posX, posY));
		ImGui::SetNextWindowSize(ImVec2(width, height));
#ifdef _DEBUG
		ImGui::Begin(windowName, 0, ImGuiWindowFlags_NoResize);
#else
		ImGui::Begin(windowName, 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
#endif
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.15f);		
		if (ImGui::Button("Atras"))
			updatePath(currentPath.parent_path().string());

		ImGui::SameLine();

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.85f);
		if (ImGui::InputText("", currentPathChar, 250))
			updatePath(std::string(currentPathChar));

		ImGui::Text("Select the files to transfer");
		ImGui::Separator();

		for (size_t i = 0; i < childs.size(); i++)
		{
			std::filesystem::path path(currentPath / childs[i].first);

			if (std::filesystem::is_directory(path)) {
				if (ImGui::Selectable(childs[i].first.c_str()))
					updatePath((currentPath / childs[i].first).string());
			}
			else
				ImGui::Checkbox(childs[i].first.c_str(), &childs[i].second);
		}

		ImGui::End();
	}
};
