#include "Sprite.h"

namespace Sparky {
	namespace Graphics {
		Sprite::Sprite(Texture * texture) :
			Renderable2D(Maths::Vec3f(0, 0, 0), Maths::Vec2f((float)texture->GetWidth(), (float)texture->GetHeight()), Maths::Vec4f(1, 1, 1, 1)), Position_(position_), Size_(size_)
		{
			texture_ = texture;
		}

		Sprite::Sprite(float x, float y, Texture * texture) :
			Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f((float)texture->GetWidth(), (float)texture->GetHeight()), Maths::Vec4f(1, 1, 1, 1)), Position_(position_), Size_(size_)
		{
			texture_ = texture;
		}

		Sprite::Sprite(float x, float y, float width, float height, Maths::Vec4f color) :
			Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), color), Position_(position_), Size_(size_)
		{}

		Sprite::Sprite(float x, float y, float width, float height, unsigned int color) :
			Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), color), Position_(position_), Size_(size_)
		{}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture) :
			Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), Maths::Vec4f(1, 1, 1, 1)), Position_(position_), Size_(size_)
		{
			texture_ = texture;
		}

		void Sprite::setUV(const std::vector<Maths::Vec2f>& uv)
		{
			uv_ = uv;
		}
	}
}