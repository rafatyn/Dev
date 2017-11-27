#pragma once

#include "buffers\Indexbuffer.h"
#include "buffers\Vertexarray.h"
#include "Shader.h"

#include "Renderer2D.h"

#include "Texture.h"

#include "../maths/maths.h"
#include "../utils/ColorFormat.h"

namespace Sparky {
	namespace Graphics {

		struct VertexData
		{
			Maths::Vec3f vertex;
			Maths::Vec2f uv;
			float tid;
			unsigned int color;
		};

		class Renderable2D {
		protected:
			Maths::Vec3f position_;
			Maths::Vec2f size_;
			unsigned int color_;
			std::vector<Maths::Vec2f> uv_;
			Texture* texture_;
		protected:
			Renderable2D() : texture_(nullptr) { setUvDefaults(); }
		public:
			Renderable2D(Maths::Vec3f postion, Maths::Vec2f size, unsigned int color) :
				position_(postion), size_(size), color_(color), texture_(nullptr)
			{ setUvDefaults(); }

			Renderable2D(Maths::Vec3f postion, Maths::Vec2f size, Maths::Vec4f color) :
				position_(postion), size_(size), texture_(nullptr)
			{
				setUvDefaults();

				color_ = ColorToUInt(color);
			}

			virtual ~Renderable2D()	{}			

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(const Maths::Vec4f& color)
			{
				color_ = ColorToUInt(color);
			}

			void setColor(const unsigned int color)
			{
				color_ = color;
			}

			inline const Maths::Vec3f& GetPosition() const { return position_; }
			inline const Maths::Vec2f& GetSize() const { return size_; }
			inline const unsigned int GetColor() const { return color_; }
			inline const std::vector<Maths::Vec2f>& GetUV() const { return uv_; }
			inline const unsigned int GetTID() const { return texture_ ? texture_->GetTID() : 0; }
		private:
			void setUvDefaults()
			{
				uv_.push_back(Maths::Vec2f(0, 0));
				uv_.push_back(Maths::Vec2f(0, 1));
				uv_.push_back(Maths::Vec2f(1, 1));
				uv_.push_back(Maths::Vec2f(1, 0));
			}
		};
	}
}