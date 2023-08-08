#include "Time.h"

namespace hk
{
	TimePoint::TimePoint(int _hour, int _minute, double _second, const TimeData& _time_lengths)
		: hour(_hour)
		, minute(_minute)
		, second(_second)
		, time_lengths(_time_lengths)
	{
	}

	void TimePoint::Wrap()
	{
		const double seconds_in_minute = time_lengths.seconds;
		const int minutes_in_hour = time_lengths.minutes;
		const int hours_in_day = time_lengths.hours;

		//This must be uninitialised so lets leave before we get any divide by zeroes
		if (seconds_in_minute <= 0 || minutes_in_hour <= 0 || hours_in_day <= 0)
		{
			return;
		}

		if (second < 0)
		{
			//+= because the number is a negative already 
			minute += static_cast<int>(std::floor(second / seconds_in_minute));
			second = seconds_in_minute + std::fmod(second, seconds_in_minute);
		}
		else if (second >= seconds_in_minute)
		{
			minute += static_cast<int>(std::floor(second / seconds_in_minute));
			second = std::fmod(second, seconds_in_minute);
		}

		if (minute < 0)
		{
			//+= because the number is a negative already
			hour += static_cast<int>(std::floor(static_cast<double>(minute) / static_cast<double>(minutes_in_hour)));
			minute = minutes_in_hour + (minute % minutes_in_hour);
		}
		else if (minute >= minutes_in_hour)
		{
			hour += static_cast<int>(std::floor(minute / minutes_in_hour));
			minute = minute % minutes_in_hour;
		}

		if (hour < 0 || hour >= hours_in_day)
		{
			hour = hours_in_day - std::abs((hour % hours_in_day));
		}
	}

	//---- TIMEPOINT OPERATORS -----
	TimePoint operator+(const TimePoint& point, const TimeData& delta)
	{
		return TimePoint{ point.hour + delta.hours, point.minute + delta.minutes, point.second + delta.seconds, point.time_lengths };
	}

	const TimePoint& operator+=(TimePoint& point, const TimeData& delta)
	{
		point.hour += delta.hours;
		point.minute += delta.minutes;
		point.second += delta.seconds;

		return point;
	}

	TimePoint operator-(const TimePoint& point, const TimeData& delta)
	{
		return TimePoint{ point.hour - delta.hours, point.minute - delta.minutes, point.second - delta.seconds, point.time_lengths };
	}

	const TimePoint& operator-=(TimePoint& point, const TimeData& delta)
	{
		point.hour -= delta.hours;
		point.minute -= delta.minutes;
		point.second -= delta.seconds;

		return point;
	}

	bool operator>(const TimePoint& lhs, const TimePoint& rhs)
	{
		if (lhs.hour > rhs.hour)
		{
			return true;
		}
		else if (lhs.hour == rhs.hour)
		{
			if (lhs.minute > rhs.minute)
			{
				return true;
			}
			else if (lhs.minute == rhs.minute)
			{
				return lhs.second > rhs.second;
			}
		}

		return false;
	}

	bool operator>=(const TimePoint& lhs, const TimePoint& rhs)
	{
		if (lhs.hour > rhs.hour)
		{
			return true;
		}
		else if (lhs.hour == rhs.hour)
		{
			if (lhs.minute > rhs.minute)
			{
				return true;
			}
			else if (lhs.minute == rhs.minute)
			{
				return lhs.second >= rhs.second;
			}
		}

		return false;
	}

	bool operator<(const TimePoint& lhs, const TimePoint& rhs)
	{
		if (lhs.hour < rhs.hour)
		{
			return true;
		}
		else if (lhs.hour == rhs.hour)
		{
			if (lhs.minute < rhs.minute)
			{
				return true;
			}
			else if (lhs.minute == rhs.minute)
			{
				return lhs.second < rhs.second;
			}
		}

		return false;
	}

	bool operator<=(const TimePoint& lhs, const TimePoint& rhs)
	{
		if (lhs.hour < rhs.hour)
		{
			return true;
		}
		else if (lhs.hour == rhs.hour)
		{
			if (lhs.minute < rhs.minute)
			{
				return true;
			}
			else if (lhs.minute == rhs.minute)
			{
				return lhs.second <= rhs.second;
			}
		}

		return false;
	}

	//----- TIMEDATA OPERATORS -----
	TimeData operator+(const TimeData& lhs, const TimeData& rhs)
	{
		return TimeData{ lhs.hours + rhs.hours, lhs.minutes + rhs.minutes, lhs.seconds + rhs.seconds };
	}

	const TimeData& operator+=(TimeData& lhs, const TimeData& rhs)
	{
		lhs.hours += rhs.hours;
		lhs.minutes += rhs.minutes;
		lhs.seconds += rhs.seconds;

		return lhs;
	}

	TimeData operator-(const TimeData& lhs, const TimeData& rhs)
	{
		return TimeData{ lhs.hours - rhs.hours, lhs.minutes - rhs.minutes, lhs.seconds - rhs.seconds };
	}

	const TimeData& operator-=(TimeData& lhs, const TimeData& rhs)
	{
		lhs.hours -= rhs.hours;
		lhs.minutes -= rhs.minutes;
		lhs.seconds -= rhs.seconds;

		return lhs;
	}

	bool operator>(const TimeData& lhs, const TimeData& rhs)
	{
		return lhs.hours > rhs.hours && lhs.minutes > rhs.minutes && lhs.seconds > rhs.seconds;
	}

	bool operator>=(const TimeData& lhs, const TimeData& rhs)
	{
		return lhs.hours >= rhs.hours && lhs.minutes >= rhs.minutes && lhs.seconds >= rhs.seconds;
	}

	bool operator<(const TimeData& lhs, const TimeData& rhs)
	{
		return lhs.hours < rhs.hours && lhs.minutes < rhs.minutes && lhs.seconds < rhs.seconds;
	}

	bool operator<=(const TimeData& lhs, const TimeData& rhs)
	{
		return lhs.hours <= rhs.hours && lhs.minutes <= rhs.minutes && lhs.seconds <= rhs.seconds;
	}
};