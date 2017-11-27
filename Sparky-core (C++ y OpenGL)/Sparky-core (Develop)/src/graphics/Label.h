#pragma once

#include "Renderable2D.h"

namespace Sparky {
	namespace Graphics {

		class Label : public Renderable2D {
		public:
			std::string text_;
			Font* font_;
			Maths::Vec3f& Lposition_;
			float x_, y_;
		public:
			Label(std::string text, float x, float y, Maths::Vec4f color);
			Label(std::string text, float x, float y, Font* font, Maths::Vec4f color);
			Label(std::string text, float x, float y, const std::string& font, Maths::Vec4f color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int size, Maths::Vec4f color);
			void submit(Renderer2D* renderer) const;
			void validate(const std::string& name, unsigned int size = 0);
		};
	}
}