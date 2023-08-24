#pragma once

#include "TilemapLayer.h"

namespace hk
{
	class TilemapObjectLayer : public TilemapLayer
	{
	public:
		bool LoadFromJson(const rapidjson::Value& layer_data) override;
		void CreateVertList(const Vector2i& map_grid_dimensions, const Tileset& tileset) override;
	};
}