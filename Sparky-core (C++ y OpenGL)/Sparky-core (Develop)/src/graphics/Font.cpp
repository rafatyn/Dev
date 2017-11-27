#include "Font.h"

namespace Sparky {
	namespace Graphics {

		Font::Font(std::string name, std::string filename, float size) :
			Name_(name), Filename_(filename), Size_(size), Scale_(Maths::Vec2f(1, 1))
		{
			FTAtlas_ = ftgl::texture_atlas_new(512, 512, 2);
			FTFont_ = ftgl::texture_font_new_from_file(FTAtlas_, size, filename.c_str());

			if (!FTAtlas_)
				SPARKY_ERROR("[Font] Cannot create font atlas");

			if (!FTFont_)
				SPARKY_ERROR("[Font] Cannot create font texture");
		}

		void Font::SetScale(float x, float y)
		{
			Scale_ = Maths::Vec2f(x, y);
		}
	}
}