#include "window.h" 

namespace Sparky {
	namespace Graphics {
		
		void error_callback(int error, const char* description);
		void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		Window::Window(const char* name, int width, int height)
		{
			width_ = width;
			height_ = height;
			name_ = name;

			if (!initGlfw())
				SPARKY_ERROR("[Window] Init failed!");

			setCallbacks();

#ifdef SPARKY_EMSCRIPTEN
			FontManager::add(new Font("Arial", "res/arial.ttf", 32));
#else
			FontManager::add(new Font("Arial", "res/arial.ttf", 32));
#endif

#ifdef SPARKY_EMSCRIPTEN
			FreeImage_Initialise();
#endif
			Audio::SoundManager::init();

			for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) {
				keys_[i] = false;
				keysState_[i] = false;
				keysTyped_[i] = false;
			}

			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
				buttons_[i] = false;
				buttonsState_[i] = false;
				buttonsClicked_[i] = false;
			}
		}

		Window::~Window()
		{
			FontManager::clean();
			TextureManager::clean();
			Audio::SoundManager::clean();
			glfwDestroyWindow(window_);
		}

		bool Window::initGlfw()
		{
			if (!glfwInit()){
				SPARKY_ERROR("[Window] Failure initialization GLFW!");
				return false;
			}

			window_ = glfwCreateWindow(width_, height_, name_, NULL, NULL);

			if (!window_){
				glfwTerminate();
				SPARKY_ERROR("[Window] Failure creating window!");
				return false;
			}

			glfwMakeContextCurrent(window_);

#ifndef SPARKY_EMSCRIPTEN
			if (glewInit() != GLEW_OK)
				SPARKY_ERROR("[Window] Failure initialization GLEW!");
#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			SPARKY_INFO("OpenGL ", (const char*)glGetString(GL_VERSION));

			return true;
		}

		void Window::setCallbacks()
		{
			glfwSetErrorCallback(error_callback);
			glfwSwapInterval(0); // Set this property to 0 to disable vsync
			glfwSetWindowUserPointer(window_, this);
			glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
			glfwSetKeyCallback(window_, keyboard_callback);
			glfwSetCursorPosCallback(window_, cursor_position_callback);
			glfwSetMouseButtonCallback(window_, mouse_button_callback);
		}

		void Window::Update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				SPARKY_ERROR("[Window] OpenGl error: ", error);

			glfwSwapBuffers(window_);
			glfwPollEvents();

			Audio::SoundManager::update();
		}

		void Window::UpdateInput() {
			for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
				keysTyped_[i] = keys_[i] && !keysState_[i];

			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
				buttonsClicked_[i] = buttons_[i] && !buttonsState_[i];

			memcpy(keysState_, keys_, MAX_KEYBOARD_KEYS);
			memcpy(buttonsState_, buttons_, MAX_MOUSE_BUTTONS);
		}

		bool Window::isClosed() const
		{
			return glfwWindowShouldClose(window_) == GL_TRUE;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::isKeyPressed(unsigned int key) const
		{
			if (key >= MAX_KEYBOARD_KEYS)
				return false;

			return keys_[key];
		}

		bool Window::isKeyTyped(unsigned int key) const
		{
			if (key >= MAX_KEYBOARD_KEYS)
				return false;

			return keysTyped_[key];
		}

		bool Window::isMousePressed(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return buttons_[button];
		}

		bool Window::isMouseClicked(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return buttonsClicked_[button];
		}

		const Maths::Vec2f& Window::GetMousePosition() const
		{
			return MousePosition_;
		}

		void error_callback(int error, const char* description)
		{
			SPARKY_ERROR("[Window] Error: ", error, "\nDescription: ", description);
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->width_  = width;
			win->height_ = height;

			glViewport(0, 0, width, height);
		}

		void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->keys_[key] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->MousePosition_.x = (float) xpos;
			win->MousePosition_.y = (float) ypos;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->buttons_[button] = action != GLFW_RELEASE;
		}
		
	}
}