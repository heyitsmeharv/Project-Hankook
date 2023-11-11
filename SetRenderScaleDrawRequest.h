#pragma once

#include <SDL2/SDL_render.h>

#include "DrawRequest.h"
#include "Vector2.h"

namespace hk
{
	class Texture;

	struct SetRenderScaleDrawRequest final : public DrawRequest
	{
		void HandleRequest() const override;

		SDL_Renderer* renderer = nullptr;
		Vector2f scale;
	};
}