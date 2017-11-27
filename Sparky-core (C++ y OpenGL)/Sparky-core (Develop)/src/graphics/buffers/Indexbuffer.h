#pragma once

#include <SparkyGl.h>
#include <utils/Log.h>

namespace Sparky {
	namespace Graphics {

		class IndexBuffer {
		private:
			GLuint BufferID_;
			GLuint Count_;
		public:
			IndexBuffer(GLushort *data, GLsizei count);
			IndexBuffer(GLuint *data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint GetCount() const { return Count_; }
		};
	}
}