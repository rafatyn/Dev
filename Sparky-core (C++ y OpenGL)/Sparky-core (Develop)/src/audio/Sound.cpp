#include "Sound.h"
#include "SoundManager.h"

namespace Sparky {
	namespace Audio {		

		Sound::Sound(const std::string & name, const std::string & filename)
			: Name_(name), Filename_(filename), Count_(0)
#ifdef SPARKY_EMSCRIPTEN
			,Playing_(false)
#else
			,Handle_(nullptr)
#endif
		{
			std::vector<std::string> split = split_string(filename, '.');

			if (split.size() < 2)
				std::cout << "Wrong sound filename" << std::endl;

#ifndef SPARKY_EMSCRIPTEN
			Sound_ = gau_load_sound_file(filename.c_str(), split[split.size() - 1].c_str());

			if (Sound_ == nullptr)
				std::cout << "Could not open the sound file" << std::endl;
#endif
		}

		Sound::~Sound()
		{
#ifdef SPARKY_EMSCRIPTEN
#else
			ga_sound_release(Sound_);
#endif
		}

		void Sound::play()
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == true)
				return;

			SoundManagerPlay(Name_.c_str());
			Playing_ = true;
#else
			if (Sound_ != nullptr) {
				if (Handle_ == nullptr || Handle_->state != GA_HANDLE_STATE_PLAYING) {
					gc_int32 quit = 0;
					Handle_ = gau_create_handle_sound(SoundManager::Mixer_, Sound_, &setFlagAndDestroyOnFinish, &quit, NULL);
					Handle_->sound = this;
					ga_handle_play(Handle_);
					Count_++;
				}
			}
#endif
		}

		void Sound::pause()
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == false)
				return;

			SoundManagerPause(Name_.c_str());
			Playing_ = false;
#else
			if (Handle_ != nullptr && Handle_->state == GA_HANDLE_STATE_PLAYING)
				ga_handle_stop(Handle_);
#endif
		}

		void Sound::resume()
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == true)
				return;

			SoundManagerPlay(Name_.c_str());
			Playing_ = true;
#else
			if (Handle_ != nullptr && Handle_->state == GA_HANDLE_STATE_STOPPED)
				ga_handle_play(Handle_);
#endif
		}

		void Sound::loop()
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == true)
				return;

			SoundManagerLoop(Name_.c_str());
			Playing_ = true;
#else
			if (Sound_ != nullptr) {
				if (Handle_ == nullptr || Handle_->state != GA_HANDLE_STATE_PLAYING) {
					gc_int32 quit = 0;
					Handle_ = gau_create_handle_sound(SoundManager::Mixer_, Sound_, &LoopOnFinish, &quit, NULL);
					Handle_->sound = this;
					ga_handle_play(Handle_);
				}
			}
#endif
		}

		void Sound::stop()
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == false)
				return;

			SoundManagerStop(Name_.c_str());
			Playing_ = false;
#else
			if (Handle_ != nullptr && Handle_->state == GA_HANDLE_STATE_PLAYING) {
				ga_handle_stop(Handle_);
				ga_handle_destroy(Handle_);
				Handle_ = nullptr;
			}
#endif
		}

		void Sound::SetGain(float gain)
		{
#ifdef SPARKY_EMSCRIPTEN
			if (Playing_ == false)
				return;

			Gain_ = gain;
			SoundManagerSetGain(Name_.c_str(), gain);
#else
			if (Handle_ != nullptr && Handle_->state == GA_HANDLE_STATE_PLAYING) {
				if (gain >= 0 && gain <= 1) {
					Gain_ = gain;
					ga_handle_setParamf(Handle_, GA_HANDLE_PARAM_GAIN, gain);
				}
			}
#endif
		}

#ifdef SPARKY_EMSCRIPTEN
#else
		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*) in_handle->sound;
			sound->Count_--;
			if(sound->Count_ == 0)
				sound->stop();
			ga_handle_destroy(in_handle);
		}

		void LoopOnFinish(ga_Handle* in_handle, void* in_context)
		{
			Sound* sound = (Sound*)in_handle->sound;
			sound->loop();
			ga_handle_destroy(in_handle);
		}
#endif
	}
}
