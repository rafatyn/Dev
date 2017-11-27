#pragma once

#include <vector>
#include "Buffer.h"

namespace Sparky {
	namespace Graphics {

		class VertexArray {
		private:
			GLuint ArrayID_;
			std::vector<Buffer*> Buffers_;
		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}