#include "KeyboardMouseDevice.h"

#include <algorithm>

namespace hk
{
	bool KeyboardMouseDevice::AreKeysPressed(const std::vector<SDL_Scancode>& keys) const
	{
		const Uint8* key_states = SDL_GetKeyboardState(nullptr);

		const bool are_all_keys_pressed = std::all_of(keys.begin(), keys.end(), [&key_states](const SDL_Scancode scan_code)
		{
			return key_states[scan_code];
		});

		return are_all_keys_pressed;
	}

	bool KeyboardMouseDevice::AreMouseButtonsPressed(const std::vector<Uint32>& mouse_buttons) const
	{
		int mouse_x, mouse_y;
		const auto mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

		const bool are_all_buttons_pressed = std::all_of(mouse_buttons.begin(), mouse_buttons.end(), [&mouse_state](const Uint32 button_code)
		{
			return (mouse_state & SDL_BUTTON(button_code)) > 0;
		});

		return are_all_buttons_pressed;
	}
}