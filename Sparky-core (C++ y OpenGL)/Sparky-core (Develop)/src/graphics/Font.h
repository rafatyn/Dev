#pragma once

#include <string>
#include <utils/Log.h>

#include "../../ext/freetype-gl/freetype-gl.h"
#include "../maths/maths.h"

namespace Sparky {
	namespace Graphics {

		class Font {
		private:
			ftgl::texture_atlas_t* FTAtlas_;
			ftgl::texture_font_t* FTFont_;

			std::string Name_;
			std::string Filename_;

			float Size_;
			Maths::Vec2f Scale_;
		public:
			Font(std::string name, std::string filename, float size);

			void SetScale(float x, float y);

			inline const std::string& getName() const { return Name_; }
			inline const std::string& getFilename() const { return Filename_; }
			inline const float getSize() const { return Size_; }
			inline const unsigned int getID() const { return FTAtlas_->id; }
			inline ftgl::texture_font_t* getFont() const { return FTFont_; }
			inline const Maths::Vec2f& getScale() const { return Scale_; }
		};
	}
}