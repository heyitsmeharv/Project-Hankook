#pragma once

#include <SDL2/SDL_ttf.h>
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
		[[nodiscard]]
		bool CreateTextureFromText(TTF_Font* font, const std::string& text, SDL_Color colour);

		void Draw		(const TextureDrawInfo& info) const;
		void DrawTiles	(const TileDrawInfo& info) const;

		int GetWidth	() const { return m_width; }
		int GetHeight	() const { return m_height; }

		bool IsValid	() const { return m_texture != nullptr; }

	private:
		std::string					m_filepath;
		std::optional<SDL_Color>	m_keyed_colour;
		SDL_Renderer*				m_renderer;
		SDL_Texture*				m_texture;
		int							m_width;
		int							m_height;
	};
}