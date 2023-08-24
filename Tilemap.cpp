//STD
#include <fstream>
#include <sstream>

//LIB
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

//SOL
#include "ErrorManager.h"
#include "Tilemap.h"
#include "TilemapObjectLayer.h"
#include "TilemapTileLayer.h"
#include "TextureManager.h"

namespace hk
{
	Tilemap::Tilemap(const std::string& filepath) 
		: Transformable()
		, Drawable()
		, m_filepath(filepath)
	{
	}

	bool Tilemap::LoadFileData()
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
					const Value& tileset_data = tilesets[ts];

					//Create a new tileset data collection
					Tileset new_tileset;
					new_tileset.LoadFromJson(tileset_data);

					m_tilesets.push_back(std::move(new_tileset));
				}

				//Load the layer info
				const Value& layers = doc["layers"];
				for (uint32_t l = 0; l < layers.Size(); ++l)
				{
					const Value& layer = layers[l];
					const std::string layer_type = layer["type"].GetString();

					std::unique_ptr<TilemapLayer> new_layer;

					if (layer_type == "tilelayer")
					{
						new_layer = std::make_unique<TilemapTileLayer>();
					}
					else if (layer_type == "objectlayer")
					{
						new_layer = std::make_unique<TilemapObjectLayer>();
					}

					if (new_layer)
					{
						new_layer->LoadFromJson(layer);
						new_layer->CreateVertList(m_grid_dimensions, m_tilesets[0]);

						m_layers.push_back(std::move(new_layer));
					}
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

	//-------------------------------------------------------------------------------------------------
	bool Tilemap::Load()
	{
		return LoadFileData();
	}

	//-------------------------------------------------------------------------------------------------
	void Tilemap::Draw(const DrawInfo& draw_info) const
	{
		for (const auto& layer : m_layers)
		{
			layer->Draw(draw_info, m_tilesets[0]);
		}
	}
}