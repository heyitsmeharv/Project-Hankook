#pragma once

#include <string>
#include <optional>
#include <SDL_render.h>
#include <vector>

#include "Vector2.h"

namespace hk
{
	struct TextureInitInfo
	{
		std::string					filepath;
		std::optional<SDL_Color>	keyed_colour = std::nullopt;
		SDL_Renderer*				renderer = nullptr;
	};

	struct TextureDrawInfo
	{
		Vector2i					position = { 0, 0 };
		Vector2i					dimensions = { -1, -1, };
		double						angle_in_deg = 0.0;
		std::optional<SDL_Rect>		clip = std::nullopt;
		std::optional<SDL_Rect>		viewport_rect = std::nullopt;
		std::optional<SDL_Point>	centre = std::nullopt;
		std::optional<SDL_Color>	colour_mod = std::nullopt;
		SDL_RendererFlip			flip = SDL_RendererFlip::SDL_FLIP_NONE;
	};

	struct TileDrawInfo
	{
		const std::vector<SDL_Vertex>*	vertices = nullptr;
		const std::vector<int>*			indices = nullptr;
		std::optional<Vector2i>			offset = std::nullopt;
	};
}