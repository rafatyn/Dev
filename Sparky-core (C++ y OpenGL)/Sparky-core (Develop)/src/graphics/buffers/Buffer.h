#pragma once

#include <SparkyGl.h>
#include <utils/Log.h>

namespace Sparky {
	namespace Graphics {

		class Buffer {
		private:
			GLuint BufferID_;
			GLuint ComponentCount_;
		public:
			Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint GetComponentCount() const { return ComponentCount_; }
		};
	}
}