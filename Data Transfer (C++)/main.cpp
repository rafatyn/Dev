#include "Dependencies\imgui\imgui.h"
#include "Dependencies\imgui\imgui_impl_glfw.h"
#include "Dependencies\imgui\imgui_impl_opengl3.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

#include <GL/gl3w.h>    // Initialize with gl3wInit()
#include <GLFW/glfw3.h> 

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Src\OriginWindow.h"
#include "Src\TargetTree.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies\stb_image.h"

std::vector<OriginDirectoryWindow> originWindows;
TargetTree* targetTree;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	for (OriginDirectoryWindow& originWindow : originWindows) {
		originWindow.updateWindowSize(window);
	}

	targetTree->updateWindowSize(window);

	glViewport(0, 0, width, height);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);	
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
	const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int windowWidth = monitor->width / 2;
	int windowHeight = monitor->height / 2;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "File transfer App", NULL, NULL);
    if (window == NULL)
        return 1;
	glfwSetWindowPos(window, (monitor->width / 2) - (windowWidth / 2), (monitor->height / 2) - (windowHeight / 2));
    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

#ifndef _DEBUG
    FreeConsole();
#endif    

    GLFWimage images; 
    images.pixels = stbi_load("icon.png", &images.width, &images.height, 0, 4); 
    glfwSetWindowIcon(window, 1, &images);
    stbi_image_free(images.pixels);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

	io.FontAllowUserScaling = true;

	ImFontConfig config;
	config.SizePixels = monitor->width / 100.0f;
	io.Fonts->AddFontDefault(&config); 

    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	originWindows.emplace_back("Origin directory 1", window, OriginDirectoryWindow::WindowPosition::TopLeft, std::string("C:\\Trabajo\\Educacion\\Src\\PACF\\trunk\\Scripts"));
	originWindows.emplace_back("Origin directory 2", window, OriginDirectoryWindow::WindowPosition::BottomLeft, std::string("C:\\Trabajo\\Educacion\\Src\\PACF\\trunk\\Scripts\\Includes"));

	targetTree = new TargetTree("Target Tree", window, std::string("\\\\WWWPRE3VM.educacion.org\\InetPub\\PA\\PACF\\Scripts"));
	
	char* genericPath = new char[1];

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::InputText("Common Path", genericPath, 250);

				ImGui::EndMenu();
			}            
            if (ImGui::Selectable(">>> Transfer <<<", false, 0, ImGui::CalcTextSize(">>> Transfer <<<")))
            {
                targetTree->transferFiles();
            }
			ImGui::EndMainMenuBar();
		}

		//----------------------------------------------------------------------------------------------------//
		std::string initialPath = originWindows[0].getCurrentPath();
		genericPath = new char[initialPath.size() + 1];
		std::copy(initialPath.begin(), initialPath.end(), genericPath);
		genericPath[initialPath.size()] = '\0';

		for (OriginDirectoryWindow& originWindow : originWindows)
		{
			std::string windowPath = originWindow.getCurrentPath();

			int i = 0;
			while (genericPath[i] != '\0' && i < windowPath.size() && genericPath[i] == windowPath[i]) i++;

			genericPath = new char[windowPath.size() + 1];
			std::copy(windowPath.begin(), windowPath.end(), genericPath);
			genericPath[i] = '\0';
		}

        targetTree->cleanSelectedFiles();

		for (OriginDirectoryWindow& originWindow : originWindows)
		{
			originWindow.show();

            std::string relativePath = originWindow.getCurrentPath().substr(std::string(genericPath).size() > originWindow.getCurrentPath().size() ? originWindow.getCurrentPath().size() : std::string(genericPath).size());
			targetTree->setSelectedFiles(originWindow.getCurrentPath(), relativePath, originWindow.getSelectedChilds());
		}
		//----------------------------------------------------------------------------------------------------//		
		targetTree->show();
		//----------------------------------------------------------------------------------------------------//			

        // Rendering
        ImGui::Render();
        
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}