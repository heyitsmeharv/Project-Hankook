#include <cmath>

#include "TilemapLayer.h"
#include "Engine.h"
#include "EngineAccess.h"
#include "Texture.h"
#include "Tileset.h"
#include "TileDrawRequest.h"

namespace hk
{
	bool TilemapLayer::LoadFromJson(const rapidjson::Value& layer_data, const int layer_index)
	{
		m_name = layer_data["name"].GetString();
		m_z_index = layer_index;
		m_position.x = layer_data["x"].GetInt();
		m_position.y = layer_data["y"].GetInt();
		m_is_visible = layer_data["visible"].GetBool();
		m_opacity = layer_data["opacity"].GetInt();

		return true;
	}

	void TilemapLayer::Draw(const Tileset& tileset, const Vector2i& offset, const float scale) const
	{
		std::unique_ptr<TileDrawRequest> draw_request = std::make_unique<TileDrawRequest>();

		draw_request->texture = tileset.image;
		draw_request->draw_info.vertices = &m_vertices;
		draw_request->draw_info.indices = &m_indices;
		draw_request->draw_info.offset = offset;
		draw_request->draw_info.scale = scale;
		draw_request->z_index = m_z_index;

		GetEngine().AddDrawRequest(std::move(draw_request));
	}
	
	Vector2f TilemapLayer::FindUVCoords(const int tile_index, const Tileset& tileset) const
	{
		const int tile_x_index = tile_index % tileset.dimensions.x;
		const float tile_y_index = std::floor((float)(tile_index / tileset.dimensions.x));

		const float normalised_tile_size_x = static_cast<float>(tileset.tile_dimensions.x) / static_cast<float>(tileset.image->GetWidth());
		const float normalised_tile_size_y = static_cast<float>(tileset.tile_dimensions.y) / static_cast<float>(tileset.image->GetHeight());

		return { normalised_tile_size_x * tile_x_index, normalised_tile_size_y * tile_y_index };
	}
}