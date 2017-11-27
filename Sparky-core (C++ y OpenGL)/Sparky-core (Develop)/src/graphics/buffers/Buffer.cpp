#include "Buffer.h"

namespace Sparky {
	namespace Graphics {

		Buffer::Buffer(GLfloat *data, GLsizei count, GLuint componentCount) :
			ComponentCount_(componentCount)
		{
			glGenBuffers(1, &BufferID_);

			if (!BufferID_)
				SPARKY_ERROR("[Buffer] Cannot generate the Buffer");

			glBindBuffer(GL_ARRAY_BUFFER, BufferID_);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &BufferID_);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, BufferID_);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}