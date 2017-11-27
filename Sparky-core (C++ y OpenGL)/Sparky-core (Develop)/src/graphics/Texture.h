#pragma once

#include <string>

#include <SparkyGl.h>
#include <utils/Log.h>

#include <FreeImage\FreeImage.h>
#include "../utils/ImageLoad.h"
#include <iostream>

namespace Sparky {
	namespace Graphics {

		class Texture {
		private:
			std::string Name_, Filename_;
			GLuint TextureID_;
			GLsizei Width_, Height_;
			unsigned int Bits_;
		public:
			Texture(const std::string& name, const std::string& filename);
			~Texture();

			void bind() const;
			void unbind() const;

			inline const std::string& GetName() const { return Name_; }
			inline const unsigned int GetWidth() const { return Width_; }
			inline const unsigned int GetHeight() const { return Height_; }
			inline const unsigned int GetTID() const { return TextureID_; }
		private:
			GLuint load();
		};
	}
}