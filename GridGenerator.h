#pragma once

#include "Vector2.h"

namespace hk
{
	struct GridComponent;

	struct GridGenerator
	{
		static inline char placeholder_char = '#';
		static bool GenerateGrid(GridComponent& grid);
	};
}