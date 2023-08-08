#include "AutomaticClock.h"

namespace hk
{
	AutomaticClock::AutomaticClock(const TimeData& time_lengths, ClockStepInfo&& step_info)
		: Clock(time_lengths)
		, m_step_info(std::move(step_info))
		, m_time_til_next_step(m_step_info.seconds_per_step)
	{
	}

	bool AutomaticClock::Update(const double delta_time)
	{
		m_time_til_next_step -= delta_time;

		if (m_time_til_next_step <= 0.0)
		{
			MoveForward(m_step_info.step_amount);
			m_time_til_next_step = m_step_info.seconds_per_step;

			printf("%dh %dm %fs \n", m_time.hour, m_time.minute, m_time.second);

			return true;
		}

		return false;
	}
}