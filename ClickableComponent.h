#pragma once

#include <SDL2/SDL_rect.h>

namespace hk
{
	struct ClickableComponent
	{
		SDL_Rect bounds;
		bool is_disabled = false;
	};
}