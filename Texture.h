#pragma once

#include <string>
#include <optional>
#include <SDL_render.h>

#include "Vector2.h"

namespace hk
{
	struct TextureInitInfo
	{
		std::string filepath;
		std::optional<SDL_Color> keyed_colour;
		SDL_Renderer* renderer;
	};

	struct TextureDrawInfo
	{
		Vector2i					position = { 0, 0 };
		double						angle_in_deg = 0.0;
		std::optional<SDL_Rect>		clip = std::nullopt;
		std::optional<SDL_Point>	centre = std::nullopt;
		SDL_RendererFlip			flip = SDL_RendererFlip::SDL_FLIP_NONE;
	};

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