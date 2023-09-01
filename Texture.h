#pragma once

#include "TextureInfos.h"

namespace hk
{
	class Texture
	{
	public:
		 Texture();
		 Texture(const TextureInitInfo& info);
		~Texture();

		void Destroy	();

		[[nodiscard]]
		bool LoadTexture();
		void Draw		(const TextureDrawInfo& info) const;
		void DrawTiles	(const TileDrawInfo& info) const;

		int GetWidth	() const { return m_width; }
		int GetHeight	() const { return m_height; }

	private:
		std::string					m_filepath;
		std::optional<SDL_Color>	m_keyed_colour;
		SDL_Renderer*				m_renderer;
		SDL_Texture*				m_texture;
		int							m_width;
		int							m_height;
	};
}