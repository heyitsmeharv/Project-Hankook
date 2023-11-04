#include <cmath>

#include "Engine.h"
#include "EngineAccess.h"
#include "ErrorManager.h"
#include "TilemapObjectLayer.h"
#include "Tileset.h"
#include "Texture.h"
#include "TextureManager.h"

namespace
{
	//std::unique_ptr<hk::GameObject> CreateGameObjectFromType(const hk::ObjectInfo& /*object_info*/)
	//{
	//	if (object_info.type == "player_spawn_point")
	//	{
	//	
	//	}
	//	else if (object_info.type == "enemy_spawn_point")
	//	{
	//	
	//	}
	//	else if (object_info.type == "treasure")
	//	{
	//		hk::GameObjectInitInfo init_info;
	//		init_info.id = object_info.name;
	//		init_info.position = object_info.position;
	//		init_info.dimensions = { static_cast<int>(object_info.dimensions.x), static_cast<int>(object_info.dimensions.y) };
	//		init_info.texture = &hk::GetEngine().GetTextureManager().GetTexture("Data\\Images\\chest_closed.png");
	//	
	//		return std::make_unique<hk::GameObject>(init_info);
	//	}
	//	else if (object_info.type == "resource_node")
	//	{
	//		hk::NodeResourceGameObjectInitInfo init_info;
	//		init_info.id = object_info.name;
	//		init_info.position = object_info.position;
	//		init_info.texture = &hk::GetEngine().GetTextureManager().GetTexture("Data\\Images\\chest_closed.png");
	//	
	//		//Stages
	//		hk::NodeStage& stage = init_info.stages.emplace_back();
	//		stage.texture = &hk::GetEngine().GetTextureManager().GetTexture("Data\\Images\\chest_closed.png");
	//		stage.resource_key = std::get<std::string>(object_info.properties.find("resource")->second.value);
	//		stage.amount_on_change = static_cast<double>(std::get<float>(object_info.properties.find("amount")->second.value));
	//	
	//		init_info.starting_stage = init_info.stages.size() - 1;
	//	
	//		return std::make_unique<hk::GameObject>(init_info);
	//	}

	//	return nullptr;
	//}
}

namespace hk
{
	bool TilemapObjectLayer::LoadFromJson(const rapidjson::Value& layer_data, const int layer_index)
	{
		if (TilemapLayer::LoadFromJson(layer_data, layer_index) == false)
		{
			return false;
		}

		if (layer_data.HasMember("objects"))
		{
			const rapidjson::Value& objects = layer_data["objects"];
			for (rapidjson::SizeType o = 0; o < objects.Size(); ++o)
			{
				const rapidjson::Value& object_data = objects[o];

				ObjectInfo object_info;
				object_info.name = object_data["name"].GetString();
				object_info.type = object_data["type"].GetString();
				object_info.position.x = object_data["x"].GetFloat();
				object_info.position.y = object_data["y"].GetFloat();
				object_info.dimensions.x = object_data["width"].GetFloat();
				object_info.dimensions.y = object_data["height"].GetFloat();
				object_info.rotation = object_data["rotation"].GetFloat();

				if (object_data.HasMember("gid"))
				{
					object_info.tile_index = object_data["gid"].GetInt() - 1;
				}

				if (object_data.HasMember("properties"))
				{
					const rapidjson::Value& properties = object_data["properties"];
					for (rapidjson::SizeType p = 0; p < properties.Size(); ++p)
					{
						const rapidjson::Value& property_data = properties[p];

						CustomProperty new_property;
						new_property.name = property_data["name"].GetString();
						
						const std::string type = property_data["type"].GetString();
						if (type == "bool")
						{
							new_property.value = property_data["value"].GetBool();
						}
						else if (type == "int")
						{
							new_property.value = property_data["value"].GetInt();
						}
						else if (type == "float")
						{
							new_property.value = property_data["value"].GetFloat();
						}
						else if (type == "string")
						{
							new_property.value = property_data["value"].GetString();
						}
						else
						{
							hk::Warn(hk::ErrorCategory::GAME_LOGIC, "Failed to load value for property %s for object %s", new_property.name.data(), object_info.name.data());
							continue;
						}

						object_info.properties.emplace(new_property.name, std::move(new_property));
					}
				}

				m_object_data.push_back(std::move(object_info));
			}
		}

		//Load Game Objects
		//for (const auto& object_data : m_object_data)
		//{
		//	if (object_data.tile_index.has_value() == false)
		//	{
		//		hk::GameObject::RootObject()->AddChild(CreateGameObjectFromType(object_data));
		//	}
		//}

		return true;
	}

	void TilemapObjectLayer::CreateVertList(const Vector2i&, const Tileset& tileset)
	{
		for (const auto& object_data : m_object_data)
		{
			if (object_data.tile_index.has_value() == false)
			{
				continue;
			}

			// find its position in the tileset texture
			const Vector2f uv = FindUVCoords(*object_data.tile_index, tileset);
			const float tu = uv.x;
			const float tv = uv.y;

			const int starting_index = static_cast<int>(m_vertices.size());
			m_vertices.insert(m_vertices.end(), 4, {});

			SDL_Vertex* quad = &m_vertices[starting_index];

			// define its 4 corners - TL = 0, TR = 1, BR = 2, BL = 3
			quad[0].position = { object_data.position.x, object_data.position.y };
			quad[1].position = { object_data.position.x + object_data.dimensions.x, object_data.position.y };
			quad[2].position = { object_data.position.x + object_data.dimensions.x, object_data.position.y + object_data.dimensions.y };
			quad[3].position = { object_data.position.x, object_data.position.y + object_data.dimensions.y };

			// define its 4 texture coordinates
			const float normalised_tile_size_x = static_cast<float>(tileset.tile_dimensions.x) / static_cast<float>(tileset.image->GetWidth());
			const float normalised_tile_size_y = static_cast<float>(tileset.tile_dimensions.y) / static_cast<float>(tileset.image->GetHeight());

			quad[0].tex_coord = { tu, tv };
			quad[1].tex_coord = { tu + normalised_tile_size_x, tv };
			quad[2].tex_coord = { tu + normalised_tile_size_x, tv + normalised_tile_size_y };
			quad[3].tex_coord = { tu, tv + normalised_tile_size_y };

			// make sure it's not transparent
			quad[0].color = { 255, 255, 255, 255 };
			quad[1].color = { 255, 255, 255, 255 };
			quad[2].color = { 255, 255, 255, 255 };
			quad[3].color = { 255, 255, 255, 255 };

			// set the indices: TL = 0, TR = 1, BR = 2, BL = 3
			m_indices.push_back(starting_index + 1);
			m_indices.push_back(starting_index + 0);
			m_indices.push_back(starting_index + 3);

			m_indices.push_back(starting_index + 2);
			m_indices.push_back(starting_index + 3);
			m_indices.push_back(starting_index + 1);
		}
	}
}