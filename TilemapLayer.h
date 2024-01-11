#pragma once

#include <memory>
#include <rapidjson/document.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>

#include "Vector2.h"

namespace hk
{
	struct Tileset;
	struct DrawInfo;
	struct TileDrawRequest;

	using VertexArray = std::vector<SDL_Vertex>;
	using IndicesArray = std::vector<int>;

	class TilemapLayer
	{
	public:
		virtual ~TilemapLayer() {}

		virtual bool LoadFromJson	(const rapidjson::Value& layer_data, const int layer_index);
		virtual void CreateVertList	(const Vector2i& map_grid_dimensions, const Tileset& tileset) = 0;

		virtual std::unique_ptr<TileDrawRequest> CreateDrawRequest	(const Tileset& tileset, const Vector2i& offset, const float scale) const;

	protected:
		Vector2f FindUVCoords(const int tile_index, const Tileset& tileset) const;

	protected:
		std::string			m_name;
		int					m_z_index;
		Vector2i			m_position;
		Vector2i			m_dimensions;
		std::vector<int>	m_tile_data;
		bool				m_is_visible;
		int					m_opacity;
		VertexArray			m_vertices;
		IndicesArray		m_indices;
	};
}