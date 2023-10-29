#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SDL2/SDL_gamecontroller.h>

namespace hk
{
	class InputCommand;

	struct GamepadCommandBinding
	{
		 GamepadCommandBinding();
		~GamepadCommandBinding();

		GamepadCommandBinding(GamepadCommandBinding&& rhs);
		GamepadCommandBinding& operator=(GamepadCommandBinding&& rhs);

		GamepadCommandBinding(const GamepadCommandBinding&) = delete;
		GamepadCommandBinding& operator=(const GamepadCommandBinding&) = delete;

		std::string						name;
		std::unique_ptr<InputCommand>	command;
	};

	struct GamepadButtonBinding : public GamepadCommandBinding
	{
		SDL_GameControllerButton button;
	};

	struct GamepadJoystickBinding : public GamepadCommandBinding
	{
		SDL_GameControllerAxis	joystick_axis;
		bool					is_positive;
	};

	class GamepadMapping
	{
	public:
		GamepadMapping();

		const std::vector<GamepadButtonBinding>&	GetButtonBindings	() const;
		const std::vector<GamepadJoystickBinding>&	GetJoystickBindings	() const;
		int											GetDeadZone			() const;

	private:
		std::vector<GamepadButtonBinding>	m_button_bindings;
		std::vector<GamepadJoystickBinding>	m_joystick_bindings;
		int									m_deadzone;
	};
}