#include "TilemapObjectLayer.h"

namespace hk
{
	bool TilemapObjectLayer::LoadFromJson(const rapidjson::Value& layer_data)
	{
		return TilemapLayer::LoadFromJson(layer_data);
	}

	void TilemapObjectLayer::CreateVertList(const Vector2i& map_grid_dimensions, const Tileset& tileset)
	{
		map_grid_dimensions; tileset;
	}
}