#pragma once

#include "Clock.h"

namespace hk
{
	struct ClockStepInfo
	{
		double seconds_per_step = 0.0;
		TimeData step_amount;
	};

	class AutomaticClock final : public Clock
	{
	public:
		AutomaticClock(const TimeData& time_lengths, ClockStepInfo&& step_info);

		void Update(const double delta_time);

	private:
		ClockStepInfo	m_step_info;
		double			m_time_til_next_step;
	};
}