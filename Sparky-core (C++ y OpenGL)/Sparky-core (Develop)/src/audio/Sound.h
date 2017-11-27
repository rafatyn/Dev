#pragma once

#include <string>
#include <iostream>

#include "../utils/StringUtils.h"

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace Sparky {
	namespace Audio {
		
		class Sound {
		private:
			std::string Name_;
			std::string Filename_;

#ifdef SPARKY_EMSCRIPTEN
#else
			ga_Sound* Sound_;
			ga_Handle* Handle_;
#endif
			bool Playing_;
			float Gain_;
			unsigned int Count_;
		public:
			Sound(const std::string& name, const std::string& filename);
			~Sound();

			void play();
			void loop();
			void pause();
			void resume();
			void stop();

			void SetGain(float gain);

#ifdef SPARKY_EMSCRIPTEN
			inline const bool isPlaying() const { return Playing_; }
#else
			inline const bool isPlaying() const { return (Handle_ != nullptr && Handle_->state == GA_HANDLE_STATE_PLAYING) ? 1 : 0; }
#endif
			inline const float GetGain() const { return Gain_; }
			inline const std::string& GetName() const { return Name_; }
			inline const std::string& GetFilename() const { return Filename_; }

#ifdef SPARKY_EMSCRIPTEN
#else
			friend void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
			friend void LoopOnFinish(ga_Handle* in_handle, void* in_context);
#endif
		};

	}
}
