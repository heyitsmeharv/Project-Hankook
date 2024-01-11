#pragma once

#include <optional>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>

#include "Texture.h"

namespace hk
{
	class RenderingSystem;
}

namespace hk::ui
{
	struct UIComponentState
	{
		friend class hk::RenderingSystem;

		std::vector<std::string>	asset_ids;
		bool						is_interactive = false;
		SDL_RendererFlip			flip_texture = SDL_FLIP_NONE;
		std::optional<SDL_Color>	colour_mod = std::nullopt;
		SDL_Color					text_colour = { 255, 255, 255, 255 };
		std::string					text;

		void SetText(const std::string& new_text)
		{
			text = new_text;
			m_is_text_dirty = true;
		}

	private:
		std::vector<const hk::Texture*> m_image_textures;
		hk::Texture						m_text_texture;
		bool							m_is_text_dirty = true;
	};	
}