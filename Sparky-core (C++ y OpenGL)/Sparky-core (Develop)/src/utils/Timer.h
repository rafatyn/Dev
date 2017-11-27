#pragma once

#define WINDOWS_TIMER 0

#if WINDOWS_TIMER
	#include <Windows.h>
#else
	#include <chrono>
#endif

namespace Sparky {

#if WINDOWS_TIMER
	class Timer {
	private:
		LARGE_INTEGER Start_;
		double frequency_;
	public:
		Timer()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			frequency_ = 1.0 / freq.QuadPart;
			QueryPerformanceCounter(&Start_);
		}

		void reset()
		{
			QueryPerformanceCounter(&Start_);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - Start_.QuadPart;
			return (float)(cycles * frequency_);
		}
	};
#else
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<HighResolutionClock> m_Start;
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_Start = HighResolutionClock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
		}
	};
#endif
}

