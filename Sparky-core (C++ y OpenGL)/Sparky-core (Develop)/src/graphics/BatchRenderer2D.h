#pragma once

#include <cstddef>
#include "Renderable2D.h"

namespace Sparky {
	namespace Graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES   32

#define SHADER_VERTEX_INDEX		0
#define	SHADER_UV_INDEX			1
#define	SHADER_TID_INDEX		2
#define	SHADER_COLOR_INDEX		3

		class BatchRenderer2D : public Renderer2D {
		private:
			IndexBuffer* IBO_;
			GLsizei IndexCount_;
			GLuint VBO_, VAO_;
			VertexData* buffer_;
#ifdef SPARKY_EMSCRIPTEN
			VertexData* bufferBase_;
#endif

			std::vector<GLuint> textures_;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawString(const std::string& text, const Maths::Vec3f& position, const Font* font, const unsigned int color) override;
			void flush() override;
			void end() override;
		private:
			void init();
		};
	}
}