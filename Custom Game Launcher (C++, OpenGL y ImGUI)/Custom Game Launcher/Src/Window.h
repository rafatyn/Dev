#pragma once

#include <GL\gl3w.h>
#include <GLFW\glfw3.h> 

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class Window
{
private:
	GLFWwindow* window;
	ImVec2 size;
	ImVec2 scale;
	ImVec2 minimizedPos;
	ImVec2 minimizedSize;
	ImVec4 screenSize;
	bool maximized;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
public:
	Window() :
		window(0), size(0, 0), minimizedPos(0, 0), minimizedSize(0, 0), screenSize(0, 0, 0, 0), maximized(false)
	{
		// Setup window
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			std::cerr << "Failed to init GLFW" << std::endl;
			return;
		}

		// GL 3.3 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// OpenGL window modifiers
		glfwWindowHint(GLFW_DECORATED, false);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, true);

		// Create window
		const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
		size = ImVec2(monitor->width / 2, monitor->height / 2);

		window = glfwCreateWindow(size.x, size.y, "Game collection App", NULL, NULL);
		if (window == NULL)
		{
			std::cerr << "Failed to create window" << std::endl;
			return;
		}

		// Set window size with DPI modifier
		glfwGetWindowContentScale(window, &scale.x, &scale.y);
		size = size * scale;

		// Set window parameters
		glfwSetWindowPos(window, (monitor->width / 2) - (size.x / 2), (monitor->height / 2) - (size.y / 2));
		glfwSetWindowSizeLimits(window, 900, 900 * 9 / 16, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
		glfwSwapInterval(1);

		// Initialize OpenGL loader
		bool err = gl3wInit() != 0;
		if (gl3wInit())
		{
			std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
			return;
		}

		// Screen dimensions
		int x, y, z, w;
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &z, &w);
		screenSize.x = static_cast<float>(x); 
		screenSize.y = static_cast<float>(y);
		screenSize.z = static_cast<float>(z);
		screenSize.w = static_cast<float>(w);

		// ImGui context
#ifdef _DEBUG
		IMGUI_CHECKVERSION();
#endif

		ImGui::CreateContext();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(NULL);

		// Configure App styles
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui::StyleColorsDark();
		style.WindowBorderSize = 0.0f;
		style.WindowRounding = 0.0f;

		ImFontConfig config;
		config.SizePixels = 30.0f;
		io.Fonts->AddFontDefault(&config);
	}

	~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void startFrame()
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void renderFrame()
	{
		ImGui::Render();

		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	inline GLFWwindow* getWindow() { return window; }
	inline bool isMaximized() { return maximized; }
	inline bool windowWillClose() { return glfwWindowShouldClose(window); }
	inline ImVec2 getWindowSize() { return size; }
	inline ImVec2 getWindowScale() { return scale; }

	void toggleMaximizeWindow()
	{
		if (maximized) {
			glfwSetWindowSize(window, minimizedSize.x, minimizedSize.y);
			glfwSetWindowPos(window, minimizedPos.x, minimizedPos.y);

			maximized = false;
		}
		else {
			int sizeX, sizeY, posX, posY;
			glfwGetWindowSize(window, &sizeX, &sizeY);
			glfwGetWindowPos(window, &posX, &posY);
			minimizedSize.x = static_cast<float>(sizeX);
			minimizedSize.y = static_cast<float>(sizeY);
			minimizedPos.x = static_cast<float>(posX);
			minimizedPos.y = static_cast<float>(posY);

			int x, y, z, w;
			glfwGetMonitorWorkarea(getWindowCurrentMonitor(), &x, &y, &z, &w);
			screenSize.x = static_cast<float>(x);
			screenSize.y = static_cast<float>(y);
			screenSize.z = static_cast<float>(z);
			screenSize.w = static_cast<float>(w);

			glfwSetWindowSize(window, screenSize.z, screenSize.w);
			glfwSetWindowPos(window, 0, 0);

			maximized = true;
		}
	}

	void minimizeWindow()
	{
		glfwIconifyWindow(window);
	}

	void closeWindow()
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void moveWindowDragged()
	{
		ImVec2 dragged = ImGui::GetMouseDragDelta(0, 0);
		int actualWindowPosX, actualWindowPosY;
		glfwGetWindowPos(window, &actualWindowPosX, &actualWindowPosY);
		glfwSetWindowPos(window, actualWindowPosX + dragged.x, actualWindowPosY + dragged.y);
	}

private:
	GLFWmonitor* getWindowCurrentMonitor()
	{
		int actualWindowPosX, actualWindowPosY;
		glfwGetWindowPos(window, &actualWindowPosX, &actualWindowPosY);

		double cursorPosX, cursorPosY;
		glfwGetCursorPos(window, &cursorPosX, &cursorPosY);
		int absoluteCursorPosX = static_cast<int>(cursorPosX) + actualWindowPosX;
		int absoluteCursorPosY = static_cast<int>(cursorPosY) + actualWindowPosY;

		int monitorsCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorsCount);

		for (int i = 0; i < monitorsCount; i++)
		{
			int monitorPosX, monitorPosY;
			glfwGetMonitorPos(monitors[i], &monitorPosX, &monitorPosY);

			const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[i]);

			if (absoluteCursorPosX >= monitorPosX && absoluteCursorPosX < (monitorPosX + videoMode->width) &&
				absoluteCursorPosY >= monitorPosY && absoluteCursorPosY < (monitorPosY + videoMode->height)) {
				return monitors[i];
			}
		}
	}

	static void glfw_error_callback(int error, const char* description)
	{
		std::cerr << "GLFW Error " << error << ": " << description << std::endl;
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->size.x = width;
		win->size.y = height;

		glViewport(0, 0, width, height);
	}

	static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->scale.x = xscale;
		win->scale.y = yscale;
	}
};
