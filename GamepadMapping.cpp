#include "InputCommand.h"
#include "GamepadMapping.h"
#include "MoveCameraInputCommand.h"

namespace hk
{
	GamepadCommandBinding::GamepadCommandBinding()
		: name()
		, button(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID)
		, joystick_axis(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID)
		, command(nullptr)

	{
	}

	GamepadCommandBinding::~GamepadCommandBinding()
	{
	}

	GamepadCommandBinding::GamepadCommandBinding(GamepadCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		button = rhs.button;
		joystick_axis = rhs.joystick_axis;
		command = std::move(rhs.command);
	}

	GamepadCommandBinding& GamepadCommandBinding::operator=(GamepadCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		button = rhs.button;
		joystick_axis = rhs.joystick_axis;
		command = std::move(rhs.command);
		return *this;
	}

	GamepadMapping::GamepadMapping()
		: m_deadzone(8000)
	{
		GamepadCommandBinding& binding = m_bindings.emplace_back();
		binding.name = "button_test";
		binding.button = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		binding.command = std::make_unique<MoveCameraInputCommand>(5.0f, 5.0f);
		
		GamepadCommandBinding& binding2 = m_bindings.emplace_back();
		binding2.name = "joystick_x_test";
		binding2.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		binding2.command = std::make_unique<MoveCameraInputCommand>(5.0f, 0.0f);
		
		GamepadCommandBinding& binding3 = m_bindings.emplace_back();
		binding3.name = "joystick_y_test";
		binding3.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		binding3.command = std::make_unique<MoveCameraInputCommand>(0.0f, 5.0f);
	}

	const std::vector<GamepadCommandBinding>& GamepadMapping::GetBindings() const
	{
		return m_bindings;
	}

	int GamepadMapping::GetDeadZone() const
	{
		return m_deadzone;
	}
}