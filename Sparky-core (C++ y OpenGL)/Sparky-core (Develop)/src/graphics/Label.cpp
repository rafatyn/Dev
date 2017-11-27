#include "Label.h"

namespace Sparky {
	namespace Graphics {
		
		Label::Label(std::string text, float x, float y, Maths::Vec4f color) :
			text_(text), x_(x), y_(y), Lposition_(position_), font_(FontManager::get("Arial", 32))
		{
			position_ = Maths::Vec3f(x, y, 0.0f);
			color_ = ColorToUInt(color);
		}

		Label::Label(std::string text, float x, float y, Font* font, Maths::Vec4f color) :
		text_(text), x_(x), y_(y), Lposition_(position_), font_(font)
		{
			position_ = Maths::Vec3f(x, y, 0.0f);
			color_ = ColorToUInt(color);
		}

		Label::Label(std::string text, float x, float y, const std::string & font, Maths::Vec4f color) :
			text_(text), x_(x), y_(y), Lposition_(position_), font_(FontManager::get(font))
		{
			position_ = Maths::Vec3f(x, y, 0.0f);
			color_ = ColorToUInt(color);

			validate(font);
		}

		Label::Label(std::string text, float x, float y, const std::string & font, unsigned int size, Maths::Vec4f color) :
			text_(text), x_(x), y_(y), Lposition_(position_), font_(FontManager::get(font, size))
		{
			position_ = Maths::Vec3f(x, y, 0.0f);
			color_ = ColorToUInt(color);

			validate(font, size);
		}

		void Label::submit(Renderer2D * renderer) const
		{
			renderer->drawString(text_, position_, font_, color_);
		}

		void Label::validate(const std::string& name, unsigned int size)
		{
			if (font_ != nullptr)
				return;

			_SPARKY_WARN("[Label] Font with name: ", name);
			if (size)
				__SPARKY_WARN(" and size = ", size);
			
			___SPARKY_WARN(" not found, Using Arial 32");

			font_ = FontManager::get("Arial", 32);
		}
	}
}