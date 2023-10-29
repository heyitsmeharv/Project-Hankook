#pragma once

#include <rapidjson/document.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>

#include "Vector2.h"

namespace hk
{
	struct Tileset;
	struct DrawInfo;

	using VertexArray = std::vector<SDL_Vertex>;
	using IndicesArray = std::vector<int>;

	class TilemapLayer
	{
	public:
		virtual ~TilemapLayer() {}

		virtual bool LoadFromJson	(const rapidjson::Value& layer_data);
		virtual void CreateVertList	(const Vector2i& map_grid_dimensions, const Tileset& tileset) = 0;

		virtual void Draw			(const Tileset& tileset) const;

	protected:
		Vector2f FindUVCoords(const int tile_index, const Tileset& tileset) const;

	protected:
		std::string			m_name;
		int					m_index;
		Vector2i			m_position;
		Vector2i			m_dimensions;
		std::vector<int>	m_tile_data;
		bool				m_is_visible;
		int					m_opacity;
		VertexArray			m_vertices;
		IndicesArray		m_indices;
	};
}