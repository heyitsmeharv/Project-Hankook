#pragma once

#include <string>

namespace hk
{
	struct ResourceChangedEvent
	{
		std::string id;
		float		previous_amount = 0.0f;
		float		new_amount = 0.0f;
		float		change_in_amount = 0.0f;
	};
}