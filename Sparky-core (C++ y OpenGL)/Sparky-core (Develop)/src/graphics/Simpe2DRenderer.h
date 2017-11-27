#pragma once

#include "Renderable2D.h"
#include "StaticSprite.h"
#include <deque>

namespace Sparky {
	namespace Graphics {

		class Simple2DRenderer : public Renderer2D {
		private:
			std::deque<const StaticSprite*> RenderQueue_;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}