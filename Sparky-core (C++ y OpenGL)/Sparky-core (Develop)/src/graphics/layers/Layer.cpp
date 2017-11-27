#include "Layer.h"

namespace Sparky {
	namespace Graphics {
		Layer::Layer(Renderer2D * renderer, Shader * shader, Maths::Mat4 ortographicMatrix) :
			Renderer_(renderer), Shader_(shader), OrtographicMatrix_(ortographicMatrix)
		{
			Shader_->enable();
#ifdef SPARKY_EMSCRIPTEN
			Shader_->SetUniform1i("texture_0", 0);
			Shader_->SetUniform1i("texture_1", 1);
			Shader_->SetUniform1i("texture_2", 2);
			Shader_->SetUniform1i("texture_3", 3);
			Shader_->SetUniform1i("texture_4", 4);
			Shader_->SetUniform1i("texture_5", 5);
			Shader_->SetUniform1i("texture_6", 6);
			Shader_->SetUniform1i("texture_7", 7);
#else
			GLint TexIDS[] = {
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31

			};

			Shader_->SetUniform1iv("textures", TexIDS, 32);
#endif
			Shader_->SetUniformMat4("pr_matrix", OrtographicMatrix_);
			Shader_->disable();
		}

		Layer::~Layer()
		{
			delete Shader_;
			delete Renderer_;

			for (int i = 0; i < Renderables_.size(); i++)
				delete Renderables_[i];
		}

		void Layer::add(Renderable2D * renderable)
		{
			Renderables_.push_back(renderable);
		}

		void Layer::render()
		{
			Shader_->enable();
			Renderer_->begin();

			for (const Renderable2D* renderable : Renderables_)
				renderable->submit(Renderer_);

			Renderer_->end();
			Renderer_->flush();
		}
	}
}