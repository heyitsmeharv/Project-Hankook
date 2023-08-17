#pragma once

#include "Time.h"

namespace hk
{
	struct TimeChangedEvent
	{
		TimePoint	old_time;
		TimePoint	new_time;
		TimeData	step_amount;
	};
}