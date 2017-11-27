#pragma once

#ifdef SPARKY_EMSCRIPTEN
	#include <emscripten/emscripten.h>
#endif

#include "utils/Timer.h"
#include "maths/maths.h"
#include "graphics/Window.h"
#include "graphics/layers/Layer.h"
#include "graphics/layers/Group.h"
#include "graphics/Label.h"
#include "graphics/Sprite.h"
#include "graphics/BatchRenderer2D.h"
#include "graphics/TextureManager.h"
#include "audio/SoundManager.h"

#ifdef SPARKY_EMSCRIPTEN
static void dispatch_main(void* function)
{
	std::function<void()>* func = (std::function<void()>*) function;
	(*func)();
}
#endif

namespace Sparky {

	class SparkyClass {
	private:
		Graphics::Window* Window_;
		Timer* Timer_;
		unsigned int FPS_, UPS_;
	protected:
		SparkyClass() :
			Window_(nullptr), Timer_(nullptr), FPS_(0), UPS_(0)
		{
			
		}

		virtual ~SparkyClass()
		{
			delete Timer_;
			delete Window_;
		}

		Graphics::Window* createWindow(const char* name, int width, int height)
		{
			Window_ = new Graphics::Window(name, width, height);
			return Window_;
		}
	
		virtual void init() = 0;
		virtual void tick() {}
		virtual void update() {}
		virtual void render() = 0;

		inline const unsigned int getFPS() const { return FPS_; }
		inline const unsigned int getUPS() const { return UPS_; }
	public:
		void start()
		{
			init();
			run();
		}
	private:
		void run()
		{
			Timer_ = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = (float)1.0 / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

#ifdef SPARKY_EMSCRIPTEN
			std::function<void()> mainLoop = [&]() {
#else
			while (!Window_->isClosed()) {
#endif
				Window_->clear();

				if (Timer_->elapsed() - updateTimer > updateTick) {
					updates++;
					Window_->UpdateInput();
					update();
					updateTimer += updateTick;
				}

				frames++;
				render();
				Window_->Update();

				if (Timer_->elapsed() - timer > 1.0f) {
					timer += 1.0f;
					FPS_ = frames;
					UPS_ = updates;
					frames = 0;
					updates = 0;
					tick();
				}
#ifdef SPARKY_EMSCRIPTEN
			};
			emscripten_set_main_loop_arg(dispatch_main, &mainLoop, 0, 1);
#else
			}
#endif
		}
	};
}