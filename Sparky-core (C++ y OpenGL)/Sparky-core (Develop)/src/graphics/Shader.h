#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SparkyGl.h>
#include <utils/Log.h>

#include "../maths/maths.h"
#include "../utils/file_utils.h"

namespace Sparky {
	namespace Graphics {

		class Shader {
		public:
			GLuint ShaderID_;
			const char *VertexPath_;
			const char *FragmentPath_;

		public:
			Shader(const char *VertexPath, const char *FrametnPath);
			~Shader();

			void SetUniform1f(const GLchar *name, const float &value);
			void SetUniform1i(const GLchar *name, const int &value );
			void SetUniform1iv(const GLchar *name, int* value, int count);
			void SetUniform1fv(const GLchar *name, float* value, int count);
			void SetUniform2f(const GLchar *name, const Maths::Vec2f &vector);
			void SetUniform3f(const GLchar *name, const Maths::Vec3f &vector);
			void SetUniform4f(const GLchar *name, const Maths::Vec4f &vector);
			void SetUniformMat4(const GLchar *name, const Maths::Mat4 &matrix);

			void enable();
			void disable();

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar *name);
		};

	}
}