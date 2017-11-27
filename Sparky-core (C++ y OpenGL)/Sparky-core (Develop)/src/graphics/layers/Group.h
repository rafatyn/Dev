#pragma once

#include "../Renderable2D.h"
#include "../Renderer2D.h"

namespace Sparky {
	namespace Graphics {

		class Group : public Renderable2D {
		private:
			std::vector<Renderable2D*> renderables_;
			Maths::Mat4 TransformationMatrix_;
		public:
			Group(const Maths::Mat4 transform);
			~Group();
			void submit(Renderer2D* renderer) const;
			void add(Renderable2D* renderable);

			Maths::Mat4& GetTransformRef() { return TransformationMatrix_; }
		};
	}
}