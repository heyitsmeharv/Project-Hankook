//STD
#include <fstream>
#include <sstream>

//LIB
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

//SOL
#include "ErrorManager.h"
#include "Tilemap.h"
#include "TextureManager.h"

namespace hk
{
	Tilemap::Tilemap(const std::string& filepath) 
		: Transformable()
		, Drawable()
		, m_filepath(filepath)
	{
	}

	bool Tilemap::LoadTerrainInfo()
	{
		using namespace rapidjson;

		std::ifstream terrain_file(m_filepath);

		if (terrain_file.good())
		{
			std::stringstream buffer;
			buffer << terrain_file.rdbuf();

			rapidjson::Document doc;
			doc.Parse(buffer.str().c_str());

			if (doc.IsObject())
			{
				//Map containing all the components for the tile (collision etc)
				//std::unordered_map<int, std::vector<std::unique_ptr<Component>>> tile_components_list;

				//Load global terrain info
				m_grid_dimensions.x = doc["width"].GetInt();
				m_grid_dimensions.y = doc["height"].GetInt();

				m_dimensions.x = m_grid_dimensions.x * doc["tilewidth"].GetInt();
				m_dimensions.y = m_grid_dimensions.y * doc["tileheight"].GetInt();

				//Load tileset info
				const Value& tilesets = doc["tilesets"];
				for (uint32_t ts = 0; ts < tilesets.Size(); ++ts)
				{
					const Value& tileset = tilesets[ts];

					//Create a new tileset data collection
					Tileset new_tileset;

					new_tileset.name = tileset["name"].GetString();
					new_tileset.tile_dimensions.x = tileset["tilewidth"].GetInt();
					new_tileset.tile_dimensions.y = tileset["tileheight"].GetInt();
					new_tileset.image_path = "Data/Tilemap/" + std::string(tileset["image"].GetString());
					new_tileset.spacing = tileset["spacing"].GetInt();
					new_tileset.margin = tileset["margin"].GetInt();
					new_tileset.dimensions.x = tileset["imagewidth"].GetInt() / new_tileset.tile_dimensions.x;
					new_tileset.dimensions.y = tileset["imageheight"].GetInt() / new_tileset.tile_dimensions.y;

					if (tileset.HasMember("tiles"))
					{
						const Value& tile_data_list = tileset["tiles"];
						for (uint32_t t = 0; t < tile_data_list.Size(); ++t)
						{
							const Value& tile_data = tile_data_list[t];
							//const int tile_index = tile_data["id"].GetInt();

							if (tile_data.HasMember("objectgroup"))
							{
								const Value& object_list = tile_data["objectgroup"]["objects"];

								for (SizeType o = 0; o < object_list.Size(); ++o)
								{
									const Value& object_data = object_list[o];

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

					new_tileset.image = &hk::TextureManager::Instance().GetTexture(new_tileset.image_path);
					m_tilesets.push_back(std::move(new_tileset));
				}

				//Load the layer info
				const Value& layers = doc["layers"];
				for (uint32_t l = 0; l < layers.Size(); ++l)
				{
					const Value& layer = layers[l];

					Layer new_layer;

					new_layer.name = layer["name"].GetString();
					new_layer.index = layer["id"].GetInt();
					new_layer.dimensions.x = layer["width"].GetInt();
					new_layer.dimensions.y = layer["height"].GetInt();
					new_layer.is_visible = layer["visible"].GetBool();
					new_layer.opacity = layer["opacity"].GetInt();

					const Value& data = layer["data"];
					if (data.IsArray() == false)
					{
						printf("Somehow the data field given in the json is not an array, something went wrong during the export from Tiled!");
						return false;
					}

					for (SizeType t = 0; t < data.Size(); ++t)
					{
						const int tile_index = data[t].GetInt();
						new_layer.tile_data.push_back(tile_index);
					
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

					m_layers.push_back(std::move(new_layer));
				}
			}
			else
			{
				hk::Fatal(hk::ErrorCategory::GFX, "Failed to parse tilemap json file (%s), this means the file is mangled", m_filepath.c_str());
				return false;
			}
		}
		else
		{
			hk::Fatal(hk::ErrorCategory::GFX, "Failed to load tilemap file, is the given path (%s) correct?", m_filepath.c_str());
			return false;
		}

		return true;
	}

	void Tilemap::InitVertsForLayers()
	{
		//get the current tileset image
		const Vector2i& tileset_dims = m_tilesets[0].dimensions;
		const Vector2i  tileset_image_size = { m_tilesets[0].image->GetWidth(), m_tilesets[0].image->GetHeight() };
		const Vector2i& tile_dims = m_tilesets[0].tile_dimensions;

		for (auto& layer : m_layers)
		{
			//layer.vertices.setPrimitiveType(sf::PrimitiveType::Quads);
			layer.vertices.resize(m_grid_dimensions.x * m_grid_dimensions.y * 4);	//4 for each vert of the quad

			for (int x = 0; x < m_grid_dimensions.x; x++)
			{
				for (int y = 0; y < m_grid_dimensions.y; y++)
				{
					//get the current tile
					const int tile_number = layer.tile_data[x + (y * m_grid_dimensions.x)] - 1;
					if (tile_number < 0)
					{
						continue;
					}

					// find its position in the tileset texture
					const int tile_x_index = tile_number % tileset_dims.x;
					const float tile_y_index = std::floor((float)(tile_number / tileset_dims.x));

					const float normalised_tile_size_x = static_cast<float>(tile_dims.x) / static_cast<float>(tileset_image_size.x);
					const float normalised_tile_size_y = static_cast<float>(tile_dims.y) /  static_cast<float>(tileset_image_size.y);

					const float tu = normalised_tile_size_x * tile_x_index;
					const float tv = normalised_tile_size_y * tile_y_index;

					// get a pointer to the current tile's quad
					const int starting_index = (x + y * m_grid_dimensions.x) * 4;
					SDL_Vertex* quad = &layer.vertices[starting_index];

					// define its 4 corners
					quad[0].position = { static_cast<float>(x * tile_dims.x),		static_cast<float>(y * tile_dims.y) };
					quad[1].position = { static_cast<float>((x + 1) * tile_dims.x), static_cast<float>(y * tile_dims.y) };
					quad[2].position = { static_cast<float>((x + 1) * tile_dims.x), static_cast<float>((y + 1) * tile_dims.y) };
					quad[3].position = { static_cast<float>(x * tile_dims.x),		static_cast<float>((y + 1) * tile_dims.y) };

					// define its 4 texture coordinates
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
					layer.indices.push_back(starting_index + 0);
					layer.indices.push_back(starting_index + 1);
					layer.indices.push_back(starting_index + 3);

					layer.indices.push_back(starting_index + 2);
					layer.indices.push_back(starting_index + 3);
					layer.indices.push_back(starting_index + 1);
				}
			}
		}
	}

	//-------------------------------------------------------------------------------------------------
	bool Tilemap::Load()
	{
		if (LoadTerrainInfo() == false)
		{
			return false;
		}

		InitVertsForLayers();
		return true;
	}

	//-------------------------------------------------------------------------------------------------
	void Tilemap::Draw(const DrawInfo& draw_info) const
	{
		for (const auto& layer : m_layers)
		{
			TileDrawInfo tile_info;
			tile_info.vertices = &layer.vertices;
			tile_info.indices = &layer.indices;
			tile_info.offset = { draw_info.viewport_rect.x, draw_info.viewport_rect.y };

			m_tilesets[0].image->DrawTiles(tile_info);
		}
	}
}