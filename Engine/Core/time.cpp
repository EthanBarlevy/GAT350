#include "time.h"

namespace vl 
{
	void Time::Tick()
	{
		clockDuration duration = clock::now() - m_startTimePoint;
		time = duration.count() / (float)clockDuration::period::den;

		duration = clock::now() - m_frameTimePoint;
		deltaTime = duration.count() / (float)clockDuration::period::den;

		m_frameTimePoint = clock::now();
	}
}

