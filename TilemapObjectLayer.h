#pragma once

#include <optional>
#include <variant>

#include "TilemapLayer.h"

namespace hk
{
	struct CustomProperty
	{
		std::string name;
		std::variant<int, bool, float, std::string, SDL_Color> value;
	};

	struct ObjectInfo
	{
		std::string					name;
		std::string					type;
		Vector2f					position;
		Vector2f					dimensions;
		float						rotation = 0.0f;
		bool						is_visible = false;
		std::optional<int>			tile_index = std::nullopt;
		std::vector<CustomProperty> properties;
	};

	class TilemapObjectLayer : public TilemapLayer
	{
	public:
		bool LoadFromJson(const rapidjson::Value& layer_data) override;
		void CreateVertList(const Vector2i& map_grid_dimensions, const Tileset& tileset) override;

	protected:
		std::vector<ObjectInfo> m_object_data;
	};
}