#include "StaticSprite.h"

namespace Sparky {
	namespace Graphics {

		StaticSprite::StaticSprite(float x, float y, float width, float height, Maths::Vec4f color, Shader& shader) :
			Renderable2D(Maths::Vec3f(x, y, 0), Maths::Vec2f(width, height), color), shader_(shader)
		{
			vertexarray_ = new VertexArray();

			GLushort indices[] =
			{
				0, 1, 2,
				2, 3, 0
			};

			indexbuffer_ = new IndexBuffer(indices, 6);

			GLfloat vertices[] =
			{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
			};

			vertexarray_->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			vertexarray_->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		}

		StaticSprite::~StaticSprite()
		{
			delete vertexarray_;
			delete indexbuffer_;
		}
	}
}