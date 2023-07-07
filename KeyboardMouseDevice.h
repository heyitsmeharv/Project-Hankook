#pragma once

#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_events.h>

#include <vector>

namespace hk
{
	class KeyboardMouseDevice
	{
	public:
		bool AreKeysPressed(const std::vector<SDL_Scancode>& keys) const;
		bool AreMouseButtonsPressed(const std::vector<Uint32>& mouse_buttons) const;
	};
}