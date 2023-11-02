#pragma once

#include "Vector2.h"
#include <optional>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

namespace hk
{
	class Texture;

	struct SpriteComponent
	{
		const hk::Texture*			texture = nullptr;
		Vector2i					dimensions = { 0, 0 };
		double						angle_in_deg = 0.0;
		float						scale = 1.0f;
		SDL_RendererFlip			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		std::optional<SDL_Point>	centre = std::nullopt;
		std::optional<SDL_Color>	colour_mod = std::nullopt;
	};
}