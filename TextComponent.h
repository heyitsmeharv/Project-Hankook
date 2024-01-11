#pragma once

#include <optional>
#include <string>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "Vector2.h"
#include "Texture.h"

namespace hk
{
	struct TextComponent
	{
		friend class RenderingSystem;

		TextComponent(SDL_Renderer* renderer);

		TTF_Font*					font = nullptr;
		int							z_index = 0;
		Vector2i					dimensions = { 0, 0 };
		double						angle_in_deg = 0.0;
		float						scale = 1.0f;
		SDL_RendererFlip			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		SDL_Color					colour = { 0, 0, 0, 255 };
		std::optional<SDL_Point>	centre = std::nullopt;

		void				SetText(const std::string& new_text);
		const std::string&	GetText() const;

	private:
		std::string					text;
		hk::Texture					texture;
	};
}