#pragma once

#include "Sound.h"
#include <vector>

#ifdef SPARKY_EMSCRIPTEN
	#include <emscripten/emscripten.h>
	#include <map>
#else
	#define GAU_THREAD_POLICY_MULTI  2
#endif

#ifdef SPARKY_EMSCRIPTEN
	extern "C" void SoundManagerAdd(const char* name, const char* filename);
	extern "C" void	SoundManagerPlay(const char* name);
	extern "C" void	SoundManagerPause(const char* name);
	extern "C" void	SoundManagerStop(const char* name);
	extern "C" void	SoundManagerLoop(const char* name);
	extern "C" void	SoundManagerSetGain(const char* name, double gain);
#endif

namespace Sparky {
	namespace Audio {
		
		class SoundManager {
		private:
			friend class Sound;

			static std::vector<Sound*> Sounds_;

#ifdef SPARKY_EMSCRIPTEN
#else
			static gau_Manager* Manager_;
			static ga_Mixer* Mixer_;
#endif
		public:
			static void init();
			static Sound* add(Sound* sound);
			static Sound* get(const std::string& name);
			static void clean();
			static void update();
		private:
			SoundManager() {}
		};
	}
}