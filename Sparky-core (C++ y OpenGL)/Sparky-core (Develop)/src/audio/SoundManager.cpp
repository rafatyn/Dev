#include "SoundManager.h"

namespace Sparky {
	namespace Audio {

#ifndef SPARKY_EMSCRIPTEN
		gau_Manager* SoundManager::Manager_ = nullptr;
		ga_Mixer* SoundManager::Mixer_ = nullptr;
#endif
		std::vector<Sound*> SoundManager::Sounds_;

		void SoundManager::init()
		{
#ifdef SPARKY_EMSCRIPTEN
			EM_ASM(
				Module.SoundManager = {};
				Module.SoundManager.Sounds_ = {};
				Module.SoundManagerAdd = function(name, filename) { Module.SoundManager.Sounds_[name] = new Audio(filename); };
				Module.SoundManagerPlay = function(name) { Module.SoundManager.Sounds_[name].play(); };
				Module.SoundManagerPause = function(name) { Module.SoundManager.Sounds_[name].pause(); };
				Module.SoundManagerStop = function(name) { Module.SoundManagerPause(name); Module.SoundManager.Sounds_[name].currentTime = 0; Module.SoundManager.Sounds_[name].loop = false; };
				Module.SoundManagerLoop = function(name) { Module.SoundManager.Sounds_[name].play(); Module.SoundManager.Sounds_[name].loop = true; };
				Module.SoundManagerSetGain = function(name, gain) { Module.SoundManager.Sounds_[name].volume = gain; };
			);
#else
			gc_initialize(0);
			Manager_ = gau_manager_create();
			Mixer_ = gau_manager_mixer(Manager_);
#endif
		}

		Sound* SoundManager::add(Sound* sound)
		{
			Sounds_.push_back(sound);
#ifdef SPARKY_EMSCRIPTEN
			SoundManagerAdd(sound->GetName().c_str(), sound->GetFilename().c_str());
#endif
			return sound;
		}

		Sound* SoundManager::get(const std::string& name)
		{
			for (Sound* sound : Sounds_)
				if (sound->GetName() == name)
					return sound;
			
			return nullptr;
		}
		
		void SoundManager::clean()
		{
			for (Sound* sound : Sounds_)
				delete sound;
#ifdef SPARKY_EMSCRIPTEN
#else
			gau_manager_destroy(Manager_);
			gc_shutdown();
#endif
		}

		void SoundManager::update()
		{
#ifdef SPARKY_EMSCRIPTEN
#else
			gau_manager_update(Manager_);
#endif
		}
	}
}