#pragma once

#include "../maths/maths.h"
#include <vector>
#include "FontManager.h"

namespace Sparky {
	namespace Graphics {
	
		class Renderable2D;

		class Renderer2D {
		protected:
			std::vector<Maths::Mat4> TransformationStack_;
			const Maths::Mat4* TransformationBack_;
		protected:
			Renderer2D()
			{
				TransformationStack_.push_back(Maths::Mat4::Identity());
				TransformationBack_ = &TransformationStack_.back();
			}
		public:
			virtual ~Renderer2D() {}

			void push(const Maths::Mat4& matrix, bool override = false)
			{
				if(override)
					TransformationStack_.push_back(matrix);
				else
					TransformationStack_.push_back(*TransformationBack_ * matrix);
				
				TransformationBack_ = &TransformationStack_.back();
			}

			void pop()
			{
				if (TransformationStack_.size() > 1)
					TransformationStack_.pop_back();

				TransformationBack_ = &TransformationStack_.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const Maths::Vec3f& position, const Font* font, const unsigned int color) {}
			virtual void end() {}
			virtual void flush() = 0;
		};
	}
}