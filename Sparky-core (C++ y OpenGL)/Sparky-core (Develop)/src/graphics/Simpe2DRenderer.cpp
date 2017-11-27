#include "Simpe2DRenderer.h"

namespace Sparky {
	namespace Graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			RenderQueue_.push_back((StaticSprite*) renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!RenderQueue_.empty())
			{
				const StaticSprite* sprite = RenderQueue_.front();
				sprite->GetVAO()->bind();
				sprite->GetIBO()->bind();

				sprite->GetShader().SetUniformMat4("ml_matrix", Maths::Mat4::Translation(sprite->GetPosition()));
				glDrawElements(GL_TRIANGLES, sprite->GetIBO()->GetCount(), GL_UNSIGNED_SHORT, 0);

				sprite->GetVAO()->unbind();
				sprite->GetIBO()->unbind();

				RenderQueue_.pop_front();
			}
		}
	}
}
