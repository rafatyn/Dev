#pragma once

#include "../Renderable2D.h"
#include "../../utils/ColorFormat.h"

namespace Sparky {
	namespace Graphics {

		class Layer {
		protected:
			Renderer2D* Renderer_;
			Shader* Shader_;
			std::vector<Renderable2D*> Renderables_;
			Maths::Mat4 OrtographicMatrix_;
		public:
			Layer(Renderer2D* renderer, Shader* shader, Maths::Mat4 ortographicMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}