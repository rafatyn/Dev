#pragma once

#include <vector>

#include "Texture.h"

namespace Sparky {
	namespace Graphics {
		
		class TextureManager {
		private:
			static std::vector<Texture*> Textures_;
		public:
			static void add(Texture* texture);
			static Texture* get(const std::string& name);
			static void clean();
		private:
			TextureManager() {}
		};
	}
}