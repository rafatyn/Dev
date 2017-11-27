#include "Texture.h"

namespace Sparky {
	namespace Graphics {
		
		Texture::Texture(const std::string& name, const std::string& filename) :
			Name_(name), Filename_(filename)
		{
			TextureID_ = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &TextureID_);
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, TextureID_);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = loadImage(Filename_.c_str(), &Width_, &Height_, &Bits_);

			if (!pixels)
				SPARKY_ERROR("[Texture] Cannot load texture image with name ", Filename_);

			GLuint result = 0;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			if (Bits_ != 24 && Bits_ != 32)
				SPARKY_ERROR("[Texture] Format bpp unsupported, BitsPerPixel (", Bits_, ")");

			GLint internalFormat = Bits_ == 32 ? GL_RGBA : GL_RGB;
			GLenum externFormat = Bits_ == 32 ?
#ifdef SPARKY_EMSCRIPTEN
			GL_RGBA : GL_RGB;
#else
			GL_BGRA : GL_BGR;
#endif
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, Width_, Height_, 0, externFormat, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;

			return result;
		}
	}
}