#pragma once

//STD
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL_render.h>

//SOL
#include "Drawable.h"
#include "TilemapLayer.h"
#include "Tileset.h"
#include "Transformable.h"
#include "Vector2.h"

namespace hk
{
	class Texture;

	class Tilemap	: public Transformable
					, public Drawable
	{
	private:
		std::string									m_filepath;
		Vector2i									m_grid_dimensions;

		std::vector<Tileset>						m_tilesets;
		std::vector<std::unique_ptr<TilemapLayer>>	m_layers;

		std::vector<int>			m_tiles;

	private:
		bool LoadFileData();

	public:
		Tilemap(const std::string& filepath);

		bool Load();

		void Draw(const DrawInfo& draw_info) const override;
	};
}