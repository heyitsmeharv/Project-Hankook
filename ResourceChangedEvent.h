#pragma once

#include <string>

namespace hk
{
	struct ResourceChangedEvent
	{
		std::string id;
		double		previous_amount = 0.0f;
		double		new_amount = 0.0f;
		double		change_in_amount = 0.0f;
	};
}