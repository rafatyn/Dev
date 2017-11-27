#include "Vertexarray.h"

namespace Sparky {
	namespace Graphics {
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &ArrayID_);

			if (!ArrayID_)
				SPARKY_ERROR("[VertexArray] Cannot generate the VertexArray");
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < Buffers_.size(); i++)
				delete Buffers_[i];

			glDeleteVertexArrays(1, &ArrayID_);
		}

		void VertexArray::addBuffer(Buffer *buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();

			Buffers_.push_back(buffer);
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(ArrayID_);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}
	}
}