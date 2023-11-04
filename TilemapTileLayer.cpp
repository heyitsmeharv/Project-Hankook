#include <cmath>

#include "TilemapTileLayer.h"
#include "Tileset.h"
#include "Texture.h"

namespace hk
{
	bool TilemapTileLayer::LoadFromJson(const rapidjson::Value& layer_data, const int layer_index)
	{
		if (TilemapLayer::LoadFromJson(layer_data, layer_index) == false)
		{
			return false;
		}

		m_dimensions.x = layer_data["width"].GetInt();
		m_dimensions.y = layer_data["height"].GetInt();

		if (layer_data.HasMember("properties"))
		{
			for (rapidjson::SizeType p = 0; p < layer_data["properties"].Size(); ++p)
			{
				const rapidjson::Value& prop = layer_data["properties"][p];

				if (strcmp(prop["name"].GetString(), "z_index") == 0)
				{
					m_z_index = prop["value"].GetInt();
					break;
				}
			}
		}

		const rapidjson::Value& data = layer_data["data"];
		if (data.IsArray() == false)
		{
			printf("Somehow the data field given in the json is not an array, something went wrong during the export from Tiled!");
			return false;
		}

		for (rapidjson::SizeType t = 0; t < data.Size(); ++t)
		{
			const int tile_index = data[t].GetInt();
			m_tile_data.push_back(tile_index);

			//const int grid_x = t % new_layer.dimensions.x;
			//const int grid_y = t / new_layer.dimensions.y;
			//
			//const auto& component_data_itr = tile_components_list.find(tile_index);
			//if (component_data_itr != tile_components_list.end())
			//{
			//	for (const auto& component : component_data_itr->second)
			//	{
			//		//We need to create a copy of the components here.
			//		//Problem is, we need to position them
			//		//If we're holding just raw Components, assuming a transform is bad as it only affects some things
			//		//Maybe change the list to be of CollisionObjects instead of raw Components??
			//
			//		//Or lets create a map for each type of collision object. It's a bit shit but better than being stuck for hours like I have been so far
			//		//So map<tile_idx, aabb>, map<tile_idx, sphere> etc etc
			//		//Then we can do look ups in each map and be able to do what's needed
			//		//This may actually give more flexibility with its verbosity
			//	}
			//}
		}

		return true;
	}

	void TilemapTileLayer::CreateVertList(const Vector2i& map_grid_dimensions, const Tileset& tileset)
	{
		const Vector2i tileset_image_size = { tileset.image->GetWidth(), tileset.image->GetHeight() };

		m_vertices.resize(map_grid_dimensions.x * map_grid_dimensions.y * 4);	//4 for each vert of the quad

		for (int x = 0; x < map_grid_dimensions.x; x++)
		{
			for (int y = 0; y < map_grid_dimensions.y; y++)
			{
				//get the current tile
				const int tile_number = m_tile_data[x + (y * map_grid_dimensions.x)] - 1;
				if (tile_number < 0)
				{
					continue;
				}

				// find its position in the tileset texture
				const Vector2f uv = FindUVCoords(tile_number, tileset);
				const float tu = uv.x;
				const float tv = uv.y;

				// get a pointer to the current tile's quad
				const int starting_index = (x + y * map_grid_dimensions.x) * 4;
				SDL_Vertex* quad = &m_vertices[starting_index];

				// define its 4 corners - TL = 0, TR = 1, BR = 2, BL = 3
				quad[0].position = { static_cast<float>(x * tileset.tile_dimensions.x),		static_cast<float>(y * tileset.tile_dimensions.y) };
				quad[1].position = { static_cast<float>((x + 1) * tileset.tile_dimensions.x), static_cast<float>(y * tileset.tile_dimensions.y) };
				quad[2].position = { static_cast<float>((x + 1) * tileset.tile_dimensions.x), static_cast<float>((y + 1) * tileset.tile_dimensions.y) };
				quad[3].position = { static_cast<float>(x * tileset.tile_dimensions.x),		static_cast<float>((y + 1) * tileset.tile_dimensions.y) };

				// define its 4 texture coordinates
				const float normalised_tile_size_x = static_cast<float>(tileset.tile_dimensions.x) / static_cast<float>(tileset_image_size.x);
				const float normalised_tile_size_y = static_cast<float>(tileset.tile_dimensions.y) / static_cast<float>(tileset_image_size.y);

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
}