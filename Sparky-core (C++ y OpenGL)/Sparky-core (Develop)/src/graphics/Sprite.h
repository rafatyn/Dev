#pragma once

#include "Renderable2D.h"

namespace Sparky {
	namespace Graphics {

		class Sprite : public Renderable2D {
		public:
			Maths::Vec3f& Position_;
			Maths::Vec2f& Size_;
		public:
			Sprite(Texture* texture);
			Sprite(float x, float y, Texture* texture);
			Sprite(float x, float y, float width, float height, Maths::Vec4f color);
			Sprite(float x, float y, float width, float height, unsigned int color);
			Sprite(float x, float y, float width, float height, Texture* texture);

			void setUV(const std::vector<Maths::Vec2f>& uv);
		};
	}
}