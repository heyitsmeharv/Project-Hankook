#pragma once

//STD
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL_render.h>

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
	public:
		Tilemap();

		bool Load(const std::string& filepath);

		void Draw() const override;

	private:
		bool LoadFileData();

	private:
		std::string									m_filepath;
		Vector2i									m_grid_dimensions;

		std::vector<Tileset>						m_tilesets;
		std::vector<std::unique_ptr<TilemapLayer>>	m_layers;

		std::vector<int>							m_tiles;
	};
}