#pragma once

#include <memory>
#include <optional>
#include <SDL2/SDL_keycode.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace hk
{
	class InputCommand;

	struct ModOverride
	{
		SDL_Keymod mod_key;
		std::unique_ptr<InputCommand> command;
	};

	struct InputCommandBinding
	{
		InputCommandBinding();
		~InputCommandBinding();

		InputCommandBinding(InputCommandBinding&& rhs);
		InputCommandBinding& operator=(InputCommandBinding&& rhs);

		InputCommandBinding(const InputCommandBinding&) = delete;
		InputCommandBinding& operator=(const InputCommandBinding&) = delete;

		std::string						name;
		std::unique_ptr<InputCommand>	default_command;
		std::vector<ModOverride>		mod_overrides;
	};

	enum class MouseWheelID
	{
		WHEEL_UP,
		WHEEL_DOWN,
		WHEEL_LEFT,
		WHEEL_RIGHT,

		NUM_OF_IDS
	};

	class KeyboardMouseMapping final
	{
	public:	
		KeyboardMouseMapping();	
	
		const InputCommandBinding* GetKeyBinding		(const SDL_KeyCode key_code) const;
		const InputCommandBinding* GetMouseButtonBinding(const Uint8 mouse_button) const;
		const InputCommandBinding* GetWheelBinding		(const MouseWheelID wheel_id) const;

	private:
		std::unordered_map<SDL_KeyCode, InputCommandBinding>	m_key_bindings;
		std::unordered_map<Uint8, InputCommandBinding>			m_mouse_bindings;
		std::unordered_map<MouseWheelID, InputCommandBinding>	m_wheel_bindings;
	};
}