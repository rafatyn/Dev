#pragma once

#include <vector>
#include "Font.h"

namespace Sparky {
	namespace Graphics {
		
		class FontManager {
		private:
			static std::vector<Font*> Fonts_;
		public:
			static void add(Font* font);
			static Font* get();
			static Font* get(const std::string& name);
			static Font* get(const std::string& name, unsigned int size);
			static void clean();
		private:
			FontManager() {}
		};
	}
}