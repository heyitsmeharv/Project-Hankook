#pragma once

//STD
#include <memory>
#include <string>
#include <vector>

//SOL
#include "TilemapLayer.h"
#include "Tileset.h"
#include "Vector2.h"

namespace hk
{
	struct TilemapComponent
	{
		TilemapComponent() = default;

		//unique_ptrs wreaking fucking havoc as per usual
		TilemapComponent(TilemapComponent&& rhs);
		TilemapComponent& operator=(TilemapComponent&& rhs);

		std::string									filepath;
		Vector2i									grid_dimensions;
		Vector2i									render_dimensions;

		std::vector<Tileset>						tilesets;
		std::vector<std::unique_ptr<TilemapLayer>>	layers;

		std::vector<int>							tiles;
	};

	bool LoadTilemapFromFile(TilemapComponent& tilemap, const std::string& filepath);

}