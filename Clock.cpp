#include "Clock.h"

#include <cmath>

namespace hk
{
	Clock::Clock(const TimeData& time_lengths)
		: m_time(0, 0, 0.0, TimeData{ 24, 60, 60.0 })
		, m_time_lengths(time_lengths)
	{
	}

	void Clock::SetTime(const TimePoint& new_time)
	{
		m_time = new_time;
		m_time.Wrap();
	}

	const TimePoint& Clock::GetTime() const
	{
		return m_time;
	}
	
	void Clock::MoveForward(const TimeData& delta)
	{
		m_time += delta;
		m_time.Wrap();
	}

	void Clock::MoveBackward(const TimeData& delta)
	{
		m_time -= delta;
		m_time.Wrap();
	}
}
