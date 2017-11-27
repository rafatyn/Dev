#pragma once

#include "Renderable2D.h"

namespace Sparky {
	namespace Graphics {

		class StaticSprite : public Renderable2D {
		private:
			VertexArray* vertexarray_;
			IndexBuffer* indexbuffer_;
			Shader& shader_;
		public:
			StaticSprite(float x, float y, float width, float height, Maths::Vec4f color, Shader& shader);
			~StaticSprite();

			inline const VertexArray* GetVAO() const { return vertexarray_; }
			inline const IndexBuffer* GetIBO() const { return indexbuffer_; }
			inline Shader& GetShader() const { return shader_; }
		};
	}
}
