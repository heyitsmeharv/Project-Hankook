//STD
#include <fstream>
#include <sstream>

//LIB
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

//SOL
#include "ErrorManager.h"
#include "TilemapComponent.h"
#include "TilemapObjectLayer.h"
#include "TilemapTileLayer.h"
#include "TextureManager.h"

namespace hk
{
	TilemapComponent::TilemapComponent(TilemapComponent&& rhs)
	{
		filepath = std::move(rhs.filepath);
		grid_dimensions = std::move(rhs.grid_dimensions);
		render_dimensions = std::move(rhs.render_dimensions);
		tilesets = std::move(rhs.tilesets);
		layers = std::move(rhs.layers);
		tiles = std::move(rhs.tiles);
	}

	TilemapComponent& TilemapComponent::operator=(TilemapComponent&& rhs)
	{
		filepath = std::move(rhs.filepath);
		grid_dimensions = std::move(rhs.grid_dimensions);
		render_dimensions = std::move(rhs.render_dimensions);
		tilesets = std::move(rhs.tilesets);
		layers = std::move(rhs.layers);
		tiles = std::move(rhs.tiles);

		return *this;
	}

	bool LoadTilemapFromFile(TilemapComponent& tilemap, const std::string& filepath)
	{
		using namespace rapidjson;

		tilemap.filepath = filepath;

		std::ifstream terrain_file(filepath);

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
				tilemap.grid_dimensions.x = doc["width"].GetInt();
				tilemap.grid_dimensions.y = doc["height"].GetInt();

				tilemap.render_dimensions.x = tilemap.grid_dimensions.x * doc["tilewidth"].GetInt();
				tilemap.render_dimensions.y = tilemap.grid_dimensions.y * doc["tileheight"].GetInt();

				//Load tileset info
				const Value& raw_tilesets = doc["tilesets"];
				for (uint32_t ts = 0; ts < raw_tilesets.Size(); ++ts)
				{
					const Value& tileset_data = raw_tilesets[ts];

					//Create a new tileset data collection
					Tileset new_tileset;
					new_tileset.LoadFromJson(tileset_data);

					tilemap.tilesets.push_back(std::move(new_tileset));
				}

				//Load the layer info
				const Value& raw_layers = doc["layers"];
				for (uint32_t l = 0; l < raw_layers.Size(); ++l)
				{
					const Value& layer = raw_layers[l];
					const std::string layer_type = layer["type"].GetString();

					std::unique_ptr<TilemapLayer> new_layer;

					if (layer_type == "tilelayer")
					{
						new_layer = std::make_unique<TilemapTileLayer>();
					}
					else if (layer_type == "objectgroup")
					{
						new_layer = std::make_unique<TilemapObjectLayer>();
					}

					if (new_layer)
					{
						new_layer->LoadFromJson(layer);
						new_layer->CreateVertList(tilemap.grid_dimensions, tilemap.tilesets[0]);

						tilemap.layers.push_back(std::move(new_layer));
					}
				}
			}
			else
			{
				hk::Fatal(hk::ErrorCategory::GFX, "Failed to parse tilemap json file (%s), this means the file is mangled", filepath.c_str());
				return false;
			}
		}
		else
		{
			hk::Fatal(hk::ErrorCategory::GFX, "Failed to load tilemap file, is the given path (%s) correct?", filepath.c_str());
			return false;
		}

		return true;
	}
}