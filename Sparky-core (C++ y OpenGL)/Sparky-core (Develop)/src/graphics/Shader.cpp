#include "Shader.h"

namespace Sparky {
	namespace Graphics {
		
		Shader::Shader(const char *VertexPath, const char *FrametnPath):
			VertexPath_(VertexPath),
			FragmentPath_(FrametnPath)
		{
			ShaderID_ = load();

			if (!ShaderID_)
				SPARKY_ERROR("[Shader] Shader error");
		}

		Shader::~Shader()
		{
			glDeleteProgram(ShaderID_);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint Vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint Fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string VertexString = read_file(VertexPath_);
			std::string FragmentString = read_file(FragmentPath_);

			if(VertexString.empty())
				SPARKY_ERROR("Cannot read the file ", VertexPath_);

			if (FragmentString.empty())
				SPARKY_ERROR("Cannot read the file ", FragmentPath_);

			const char *VertexChar = VertexString.c_str();
			const char *FragmentChar = FragmentString.c_str();

			glShaderSource(Vertex, 1, &VertexChar, NULL);
			glCompileShader(Vertex);

			GLint result;
			glGetShaderiv(Vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE){
				GLint length;
				glGetShaderiv(Vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(Vertex, length, &length, &error[0]);
				glDeleteShader(Vertex);
				SPARKY_ERROR("Shader: ", VertexPath_, &error[0]);

				return 0;
			}

			glShaderSource(Fragment, 1, &FragmentChar, NULL);
			glCompileShader(Fragment);

			glGetShaderiv(Fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE){
				GLint length;
				glGetShaderiv(Fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(Fragment, length, &length, &error[0]);
				glDeleteShader(Fragment);
				SPARKY_ERROR("Shader: ", FragmentPath_, &error[0]);

				return 0;
			}

			glAttachShader(program, Vertex);
			glAttachShader(program, Fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(Vertex);
			glDeleteShader(Fragment);

			return program;
		}

		void Shader::enable()
		{
			glUseProgram(ShaderID_);
		}

		void Shader::disable()
		{
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar *name)
		{
			return glGetUniformLocation(ShaderID_, name);
		}

		void Shader::SetUniform1f(const GLchar *name, const float &value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::SetUniform1i(const GLchar *name, const int &value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::SetUniform1iv(const GLchar *name, int* value, int count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::SetUniform1fv(const GLchar *name, float* value, int count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::SetUniform2f(const GLchar *name, const Maths::Vec2f &vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::SetUniform3f(const GLchar *name, const Maths::Vec3f &vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::SetUniform4f(const GLchar *name, const Maths::Vec4f &vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::SetUniformMat4(const GLchar *name, const Maths::Mat4 &matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}
	}
}