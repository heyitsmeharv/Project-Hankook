#include "Tileset.h"
#include "ErrorManager.h"
#include "TextureManager.h"

namespace hk
{
	void Tileset::LoadFromJson(const rapidjson::Value& tileset_data)
	{
		name = tileset_data["name"].GetString();
		tile_dimensions.x = tileset_data["tilewidth"].GetInt();
		tile_dimensions.y = tileset_data["tileheight"].GetInt();
		image_path = "Data/Tilemap/" + std::string(tileset_data["image"].GetString());
		spacing = tileset_data["spacing"].GetInt();
		margin = tileset_data["margin"].GetInt();
		dimensions.x = tileset_data["imagewidth"].GetInt() / tile_dimensions.x;
		dimensions.y = tileset_data["imageheight"].GetInt() / tile_dimensions.y;
		image = &hk::TextureManager::Instance().GetTexture(image_path);

		if (tileset_data.HasMember("tiles"))
		{
			const rapidjson::Value& tile_data_list = tileset_data["tiles"];
			for (uint32_t t = 0; t < tile_data_list.Size(); ++t)
			{
				const rapidjson::Value& tile_data = tile_data_list[t];
				//const int tile_index = tile_data["id"].GetInt();

				if (tile_data.HasMember("objectgroup"))
				{
					const rapidjson::Value& object_list = tile_data["objectgroup"]["objects"];

					for (rapidjson::SizeType o = 0; o < object_list.Size(); ++o)
					{
						const rapidjson::Value& object_data = object_list[o];

						const std::string type = object_data["type"].GetString();

						if (type == "COLLISION_BOX")
						{
							// const float box_width = object_data["width"].GetFloat();
							// const float box_height = object_data["height"].GetFloat();
							// 
							// const float x_offset = object_data["x"].GetFloat();
							// const float y_offset = object_data["y"].GetFloat();
							// 
							// std::unique_ptr<Component> aabb = std::make_unique<AABBCollisionComponent>(sf::Vector2f{ x_offset, y_offset }, sf::Vector2f{ box_width * 0.5f, box_height * 0.5f }, CollisionBitset{}, CollisionBitset{});
							// tile_components_list[tile_index].push_back(std::move(aabb));
						}
						else if (type == "COLLISION_POLYGON")
						{

						}
						else
						{
							hk::Fatal(hk::ErrorCategory::GFX, "Failed to parse object data as the type wasn't recognised/setup in code");
						}
					}
				}
			}
		}
	}
}