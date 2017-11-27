#include "BatchRenderer2D.h"

namespace Sparky {
	namespace Graphics {

		BatchRenderer2D::BatchRenderer2D() :
			IndexCount_(0)
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete IBO_;
			glDeleteBuffers(1, &VBO_);
			glDeleteVertexArrays(1, &VAO_);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &VAO_);
			glGenBuffers(1, &VBO_);

			glBindVertexArray(VAO_);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			IBO_ = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);

#ifdef SPARKY_EMSCRIPTEN
			bufferBase_ = new VertexData[RENDERER_MAX_SPRITES * 4];
#endif
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO_);
#ifdef SPARKY_EMSCRIPTEN
			buffer_ = bufferBase_;
#else
			buffer_ = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#endif
		}

		void BatchRenderer2D::submit(const Renderable2D *renderable)
		{
			const Maths::Vec3f& position = renderable->GetPosition();
			const unsigned int color = renderable->GetColor();
			const Maths::Vec2f& size = renderable->GetSize();
			const std::vector<Maths::Vec2f>& uv = renderable->GetUV();
			const unsigned int tid = renderable->GetTID();

			float ts = 0.0f;

			if (tid > 0) {
				bool found = false;

				for (int i = 0; i < textures_.size(); i++) {
					if (textures_[i] == tid) {
						ts = (float)i + 1;
						found = true;
						break;
					}
				}

				if (!found) {
					if (textures_.size() >= RENDERER_MAX_TEXTURES) {
						end();
						flush();
						begin();
					}

					textures_.push_back(tid);
					ts = (float)textures_.size();
				}
			}
			
			buffer_->vertex = *TransformationBack_ * position;
			buffer_->uv = uv[0];
			buffer_->tid = ts;
			buffer_->color = color;
			buffer_++;

			buffer_->vertex = *TransformationBack_ * Maths::Vec3f(position.x, position.y + size.y, position.z);
			buffer_->uv = uv[1];
			buffer_->tid = ts;
			buffer_->color = color;
			buffer_++;

			buffer_->vertex = *TransformationBack_ * Maths::Vec3f(position.x + size.x, position.y + size.y, position.z);
			buffer_->uv = uv[2];
			buffer_->tid = ts;
			buffer_->color = color;
			buffer_++;

			buffer_->vertex = *TransformationBack_ * Maths::Vec3f(position.x + size.x, position.y, position.z);
			buffer_->uv = uv[3];
			buffer_->tid = ts;
			buffer_->color = color;
			buffer_++;

			IndexCount_ += 6;
		}

		void BatchRenderer2D::drawString(const std::string& text, const Maths::Vec3f& position, const Font* font, const unsigned int color)
		{
			float ts = 0.0f;
			bool found = false;

			for (int i = 0; i < textures_.size(); i++) {
				if (textures_[i] == font->getID()) {
					ts = (float)i + 1;
					found = true;
					break;
				}
			}

			if (!found) {
				if (textures_.size() >= RENDERER_MAX_TEXTURES) {
					end();
					flush();
					begin();
				}

				textures_.push_back(font->getID());
				ts = (float)textures_.size();
			}
			
			const Maths::Vec2f scale = font->getScale();

			float x = position.x;

			for (int i = 0; i < text.length(); i++) {

				char c = text.at(i);
				texture_glyph_t *glyph = texture_font_get_glyph(font->getFont(), c);

				if (glyph != NULL) {

					if (i > 0)
						x += texture_glyph_get_kerning(glyph, text[i - 1]) / scale.x;
					
					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					buffer_->vertex = *TransformationBack_ * Maths::Vec3f(x0, y0, 0.0f);
					buffer_->uv = Maths::Vec2f(u0, v0);
					buffer_->tid = ts;
					buffer_->color = color;
					buffer_++;

					buffer_->vertex = *TransformationBack_ * Maths::Vec3f(x0, y1, 0.0f);
					buffer_->uv = Maths::Vec2f(u0, v1);
					buffer_->tid = ts;
					buffer_->color = color;
					buffer_++;

					buffer_->vertex = *TransformationBack_ * Maths::Vec3f(x1, y1, 0.0f);
					buffer_->uv = Maths::Vec2f(u1, v1);
					buffer_->tid = ts;
					buffer_->color = color;
					buffer_++;

					buffer_->vertex = *TransformationBack_ * Maths::Vec3f(x1, y0, 0.0f);
					buffer_->uv = Maths::Vec2f(u1, v0);
					buffer_->tid = ts;
					buffer_->color = color;
					buffer_++;

					IndexCount_ += 6;

					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer2D::flush()
		{
			for (int i = 0; i < textures_.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textures_[i]);
			}

			glBindVertexArray(VAO_);
			IBO_->bind();

			glDrawElements(GL_TRIANGLES, IndexCount_, GL_UNSIGNED_INT, NULL);

			IBO_->unbind();
			glBindVertexArray(0);

			IndexCount_ = 0;
			textures_.clear();
		}

		void BatchRenderer2D::end()
		{
#ifdef SPARKY_EMSCRIPTEN
			glBindBuffer(GL_ARRAY_BUFFER, VBO_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, (buffer_ - bufferBase_) * RENDERER_VERTEX_SIZE, bufferBase_);
			buffer_ = bufferBase_;
#else
			glUnmapBuffer(GL_ARRAY_BUFFER);
#endif
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}		
	}
}