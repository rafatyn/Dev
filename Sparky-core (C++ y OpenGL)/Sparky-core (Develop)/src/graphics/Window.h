#include <iostream>

#include <SparkyGl.h>
#include <utils/Log.h>

#include "FontManager.h"
#include "TextureManager.h"
#include "../audio/SoundManager.h"
#include "../maths/maths.h"

namespace Sparky {
	namespace Graphics {

#define MAX_KEYBOARD_KEYS 512
#define MAX_MOUSE_BUTTONS 8

		class Window {
		private: 
			int width_, height_;
			const char *name_;
			GLFWwindow *window_;

			bool keys_[MAX_KEYBOARD_KEYS];
			bool keysState_[MAX_KEYBOARD_KEYS];
			bool keysTyped_[MAX_KEYBOARD_KEYS];
			bool buttons_[MAX_MOUSE_BUTTONS];
			bool buttonsState_[MAX_MOUSE_BUTTONS];
			bool buttonsClicked_[MAX_MOUSE_BUTTONS];
			
			Maths::Vec2f MousePosition_;
		public:
			Window(const char* name, int width, int height);
			~Window();

			void Update();
			void UpdateInput();
			bool isClosed() const;
			void clear() const;

			bool isKeyPressed(unsigned int key) const;
			bool isKeyTyped(unsigned int key) const;
			bool isMousePressed(unsigned int button) const;
			bool isMouseClicked(unsigned int button) const;
			const Maths::Vec2f& GetMousePosition() const;

			inline int GetWidth() const { return width_; }
			inline int GetHeight() const { return height_; }

		private:
			bool initGlfw();
			void setCallbacks();

		private:
			friend void error_callback(int error, const char* description);
			friend void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		};

	}
}