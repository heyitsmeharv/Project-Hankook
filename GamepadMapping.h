#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SDL_gamecontroller.h>

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
		SDL_GameControllerButton		button;
		SDL_GameControllerAxis			joystick_axis;
		std::unique_ptr<InputCommand>	command;
	};

	class GamepadMapping final
	{
	public:
		GamepadMapping();

		const std::vector<GamepadCommandBinding>&	GetBindings() const;
		int											GetDeadZone() const;

	private:
		std::vector<GamepadCommandBinding>	m_bindings;
		int									m_deadzone;
	};
}