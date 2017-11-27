#include "Group.h"

namespace Sparky {
	namespace Graphics {

		Group::Group(const Maths::Mat4 transform) :
			TransformationMatrix_(transform)
		{}

		Group::~Group()
		{
			for (int i = 0; i < renderables_.size(); i++)
				delete renderables_[i];
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push(TransformationMatrix_);

			for (Renderable2D* renderable : renderables_)
				renderable->submit(renderer);

			renderer->pop();
		}

		void Group::add(Renderable2D * renderable)
		{
			renderables_.push_back(renderable);
		}
	}
}