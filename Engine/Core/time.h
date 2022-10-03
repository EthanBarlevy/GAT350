#pragma once
#include <chrono>

namespace vl
{
	class Time 
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clockDuration = clock::duration;
		using clockRep = clock::rep;

	public:
		Time() : 
			m_startTimePoint{ clock::now() },
			m_frameTimePoint{ clock::now() }
		{}

		void Tick();
		void Reset() { m_startTimePoint = clock::now(); }

	public:
		double deltaTime = 0;
		double time = 0;

	private:
		clock::time_point m_startTimePoint; // start of app
		clock::time_point m_frameTimePoint; // start of frame
	};
}