#pragma once

#include <cmath>

namespace hk
{
	// Why have a different struct for the same data structure? 
	// Basically strong typing for clarity and safety. Adding a timepoint to a timepoint seems weird
	// Point + Point = nonsense, the same as maths with a Vector vs Point
	struct TimeData
	{
		int		hours;
		int		minutes;
		double	seconds;
	};

	struct TimePoint
	{
		int		 hour;
		int		 minute;
		double	 second;
		TimeData time_lengths;

		TimePoint() = default;
		TimePoint(int _hour, int _minute, double _second, const TimeData& _time_lengths);
		void Wrap();
	};

	//----- TimePoint Operators -----
	TimePoint operator+(const TimePoint& point, const TimeData& delta);
	const TimePoint& operator+=(TimePoint& point, const TimeData& delta);

	TimePoint operator-(const TimePoint& point, const TimeData& delta);
	const TimePoint& operator-=(TimePoint& point, const TimeData& delta);

	bool operator>(const TimePoint& lhs, const TimePoint& rhs);
	bool operator>=(const TimePoint& lhs, const TimePoint& rhs);
	bool operator<(const TimePoint& lhs, const TimePoint& rhs);
	bool operator<=(const TimePoint& lhs, const TimePoint& rhs);

	//----- TimeData Operators -----
	TimeData operator+(const TimeData& lhs, const TimeData& rhs);
	const TimeData& operator+=(TimeData& lhs, const TimeData& rhs);

	TimeData operator-(const TimeData& lhs, const TimeData& rhs);
	const TimeData& operator-=(TimeData& lhs, const TimeData& rhs);

	bool operator>(const TimeData& lhs, const TimeData& rhs);
	bool operator>=(const TimeData& lhs, const TimeData& rhs);
	bool operator<(const TimeData& lhs, const TimeData& rhs);
	bool operator<=(const TimeData& lhs, const TimeData& rhs);
}