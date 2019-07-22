#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <thread>

class TargetTree
{
private:
	char* currentPathChar;
	std::filesystem::path currentPath;

	std::vector<std::string> originSelectedFiles;
	std::vector<std::string> selectedFiles;

    bool copying = false;

	ImGuiTreeNodeFlags treeFolderFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	ImGuiTreeNodeFlags treeFileFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	const char* windowName;
	int posX, posY, width, height, winWidth, winHeight;

	void drawTree(std::filesystem::path path)
	{
        try {
            for (const std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path))
            {
                if (entry.is_directory())
                {
                    bool node_open = ImGui::TreeNodeEx(entry.path().filename().string().c_str(), treeFolderFlags);
                    if (node_open)
                    {
                        drawTree(path / entry.path().filename().string());
                        ImGui::TreePop();
                    }
                }
                else if (entry.is_regular_file())
                {
                    size_t i;
                    for (i = 0; i < selectedFiles.size(); i++)
                    {
                        if (selectedFiles[i] == entry.path().string())
                        {
                            if (std::filesystem::last_write_time(originSelectedFiles[i]) == std::filesystem::last_write_time(entry.path()))
                            {
                                ImGui::PushStyleColor(ImGuiCol_Header, (ImVec4)ImColor(0.18f, 0.75f, 0.12f, 0.5f));
                                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor(0.18f, 0.75f, 0.12f, 0.5f));
                            }
                            else
                            {
                                ImGui::PushStyleColor(ImGuiCol_Header, (ImVec4)ImColor(1.0f, 0.81f, 0.0f, 0.5f));
                                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor(1.0f, 0.81f, 0.0f, 0.5f));
                            }
                            ImGui::TreeNodeEx(entry.path().filename().string().c_str(), treeFileFlags | ImGuiTreeNodeFlags_Selected);
                            ImGui::PopStyleColor();
                            ImGui::PopStyleColor();
                            break;
                        }
                    }
                    if (i == selectedFiles.size())
                        ImGui::TreeNodeEx(entry.path().filename().string().c_str(), treeFileFlags);
                }
            }
        }
        catch (std::filesystem::filesystem_error error)
        {
            ImGui::OpenPopup("ERROR");

            if (ImGui::BeginPopupModal("ERROR", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::SameLine(0, (ImGui::CalcTextSize("Can't connect to target directory").x / 2) - 15);
                ImGui::Spinner("Spinner", 15, 5, ImGui::GetColorU32(ImGuiCol_ButtonHovered));
                ImGui::Text("Can't connect to target directory");
            }
            ImGui::EndPopup();
        }
	}

public:
	TargetTree(const char* name, GLFWwindow* window, std::string path = "")
	{
		windowName = name;

		if (path != "")
			updatePath(path);
		else
			updatePath(std::filesystem::current_path().string());

		updateWindowSize(window);
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
		
        const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
        float fontSize = monitor->width / 100.0f;
        float framePadding = ImGui::GetStyle().FramePadding.y;
        int padding = round(fontSize + framePadding);

		posX = winWidth / 2; posY = padding;
		width = winWidth / 2; height = winHeight - padding;
	}

	void setSelectedFiles(std::filesystem::path originPath, std::string path, std::vector<std::string> selectedFiles)
	{
        if (!copying)
        {
            std::filesystem::path dirPath(path);

            for (std::string selectedFile : selectedFiles)
            {
                if (path.size() != 0)
                    this->selectedFiles.emplace_back(currentPath.string() + (dirPath / selectedFile).string());
                else
                    this->selectedFiles.emplace_back((currentPath / selectedFile).string());

                this->originSelectedFiles.emplace_back((originPath / selectedFile).string());
            }
        }
	}

	std::string getCurrentPath()
	{
		return currentPath.string();
	}

    void cleanSelectedFiles()
    {
        if (!copying)
        {
            this->originSelectedFiles.clear();
            this->selectedFiles.clear();
        }
    }

    void transferFiles()
    {
        auto f = [&]() {
            for (size_t i = 0; i < selectedFiles.size(); i++)
            {
                std::ifstream inFile(originSelectedFiles[i], std::ifstream::in);

                if (inFile.is_open())
                {
                    std::ofstream outFile(selectedFiles[i], std::ofstream::out);

                    if (outFile.is_open())
                    {
                        outFile << inFile.rdbuf();
                    }

                    outFile.close();

                    std::filesystem::last_write_time(selectedFiles[i], std::filesystem::last_write_time(originSelectedFiles[i]));
                }

                inFile.close();
            }

            copying = false;
        };

        if (!copying) {
            copying = true;
            std::thread* thread_object = new std::thread(f);
        }
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

		ImGui::Separator();
	
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 1);
		drawTree(currentPath);
		ImGui::PopStyleVar();

        if (copying) {
            ImGui::OpenPopup("Process");

            if (ImGui::BeginPopupModal("Process", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::SameLine(0, (ImGui::CalcTextSize("Copying files").x / 2) - 15);
                ImGui::Spinner("Spinner", 15, 5, ImGui::GetColorU32(ImGuiCol_ButtonHovered));
                ImGui::Text("Copying files");
            }
            ImGui::EndPopup();
        }

		ImGui::End();
	}
};
