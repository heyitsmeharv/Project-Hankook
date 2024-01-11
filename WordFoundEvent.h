#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

namespace hk
{
	struct WordFoundEvent
	{
		std::string				found_word;
		std::vector<Vector2i>	cell_list;
	};
}