#pragma once

//STD
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL_render.h>

//SOL
#include "Drawable.h"
#include "Transformable.h"
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
	};

	using VertexArray = std::vector<SDL_Vertex>;
	using IndicesArray = std::vector<int>;
	struct Layer
	{
		std::string			name;
		int					index;
		Vector2i			dimensions;
		std::vector<int>	tile_data;
		bool				is_visible;
		int					opacity;
		VertexArray			vertices;
		IndicesArray		indices;
	};

	class Tilemap	: public Transformable
					, public Drawable
	{
	private:
		std::string				m_filepath;
		Vector2i				m_dimensions;

		std::vector<Tileset>	m_tilesets;
		std::vector<Layer>		m_layers;

		std::vector<int>		m_tiles;

	private:
		bool LoadTerrainInfo();
		void InitVertsForLayers();

	public:
		Tilemap(const std::string& filepath);

		bool Load();

		void Draw(const DrawInfo& draw_info) const override;
	};
}