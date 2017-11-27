#include "Indexbuffer.h"

namespace Sparky {
	namespace Graphics {

		IndexBuffer::IndexBuffer(GLushort *data, GLsizei count) :
			Count_(count)
		{
			glGenBuffers(1, &BufferID_);

			if (!BufferID_)
				SPARKY_ERROR("[Buffer] Cannot generate the buffer");

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::IndexBuffer(GLuint *data, GLsizei count) :
			Count_(count)
		{
			glGenBuffers(1, &BufferID_);

			if (!BufferID_)
				SPARKY_ERROR("[IndexBuffer] Cannot generate the IndexBuffer");

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID_);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &BufferID_);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID_);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}