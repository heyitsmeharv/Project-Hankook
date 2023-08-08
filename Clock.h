#pragma once

#include "Time.h"

namespace hk
{
	class Clock
	{
	public:
		Clock(const TimeData& time_lengths);

		void				SetTime	(const TimePoint& new_time);
		const TimePoint&	GetTime	() const;

		void MoveForward	(const TimeData& delta);
		void MoveBackward	(const TimeData& delta);

	protected:
		TimePoint	m_time;
		TimeData	m_time_lengths;
	};
}