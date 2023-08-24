#include "TilemapLayer.h"
#include "Drawable.h"
#include "Texture.h"
#include "Tileset.h"

namespace hk
{
	bool TilemapLayer::LoadFromJson(const rapidjson::Value& layer_data)
	{
		m_name = layer_data["name"].GetString();
		m_index = layer_data["id"].GetInt();
		m_position.x = layer_data["x"].GetInt();
		m_position.y = layer_data["y"].GetInt();
		m_is_visible = layer_data["visible"].GetBool();
		m_opacity = layer_data["opacity"].GetInt();

		return true;
	}

	void TilemapLayer::Draw(const DrawInfo& draw_info, const Tileset& tileset) const
	{
		TileDrawInfo tile_info;
		tile_info.vertices = &m_vertices;
		tile_info.indices = &m_indices;
		tile_info.offset = { draw_info.viewport_rect.x, draw_info.viewport_rect.y };

		tileset.image->DrawTiles(tile_info);
	}
}