#pragma once

#include <rapidjson/document.h>
#include <string>

#include "Vector2.h"

namespace hk
{
	class Texture;

	struct Tileset
	{
		using TileIndex = int;
		//using CollisionData = std::unordered_map<TileIndex, AABBCollisionComponent>;

		//This could definitely be packed more efficiently but I like this ordering
		std::string			name;
		Vector2i			dimensions;
		Vector2i			tile_dimensions;
		std::string			image_path;
		const hk::Texture*	image;
		int					spacing;
		int					margin;
		//CollisionData	tile_collision_data;

		void LoadFromJson(const rapidjson::Value& tileset_data);
	};
}