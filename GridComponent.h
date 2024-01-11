#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "Vector2.h"

namespace hk
{
	enum Orientations { VERTICAL, HORIZONTAL, DIAGONAL, NUM_OF_ORIENTATIONS };

	struct WordInfo
	{
		bool					is_found = false;
		Orientations			orientation;
		std::vector<Vector2i>	locations;
	};

	struct GridComponent
	{
		int width = 0;
		int height = 0;

		std::vector<char> cell_list;
		std::vector<std::string> word_list;
		std::unordered_map<std::string, WordInfo> word_infos;

		int CoordToIndex(Vector2i coord) const
		{
			return (coord.y * width) + coord.x;
		}

		bool IsComplete() const
		{
			return std::all_of(word_infos.begin(), word_infos.end(), [](const auto& itr) { return itr.second.is_found; });
		}
	};
}