#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SDL_gamecontroller.h>

namespace hk
{
	class Command;

	struct GamepadCommandBinding
	{
		std::string					name;
		SDL_GameControllerButton	button			= SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerAxis		joystick_axis	= SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID;
		std::unique_ptr<Command>	command			= nullptr;
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