#include "Clock.h"

#include <cmath>
#include "TimeChangedEvent.h"

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
		TimeChangedEvent msg;
		msg.old_time = m_time;
		msg.step_amount = delta;

		m_time += delta;
		m_time.Wrap();

		msg.new_time = m_time;
		NotifyListeners(msg);
	}

	void Clock::MoveBackward(const TimeData& delta)
	{
		MoveForward(-delta);
	}
}
