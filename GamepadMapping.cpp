#include "InputCommand.h"
#include "GamepadMapping.h"
#include "MoveCameraInputCommand.h"

namespace hk
{
	GamepadCommandBinding::GamepadCommandBinding()
		: name()
		, command(nullptr)

	{
	}

	GamepadCommandBinding::~GamepadCommandBinding()
	{
	}

	GamepadCommandBinding::GamepadCommandBinding(GamepadCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		command = std::move(rhs.command);
	}

	GamepadCommandBinding& GamepadCommandBinding::operator=(GamepadCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		command = std::move(rhs.command);
		return *this;
	}

	GamepadMapping::GamepadMapping()
		: m_deadzone(8000)
	{
		GamepadButtonBinding& button_binding = m_button_bindings.emplace_back();
		button_binding.name = "button_test";
		button_binding.button = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		button_binding.command = std::make_unique<MoveCameraInputCommand>(5.0f, 5.0f);
		
		GamepadJoystickBinding& right_binding = m_joystick_bindings.emplace_back();
		right_binding.name = "joystick_right_test";
		right_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		right_binding.is_positive = true;
		right_binding.command = std::make_unique<MoveCameraInputCommand>(5.0f, 0.0f);
		
		GamepadJoystickBinding& left_binding = m_joystick_bindings.emplace_back();
		left_binding.name = "joystick_left_test";
		left_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		left_binding.is_positive = false;
		left_binding.command = std::make_unique<MoveCameraInputCommand>(-5.0f, 0.0f);

		GamepadJoystickBinding& up_binding = m_joystick_bindings.emplace_back();
		up_binding.name = "joystick_up_test";
		up_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		up_binding.is_positive = false;
		up_binding.command = std::make_unique<MoveCameraInputCommand>(0.0f, -5.0f);

		GamepadJoystickBinding& down_binding = m_joystick_bindings.emplace_back();
		down_binding.name = "joystick_down_test";
		down_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		down_binding.is_positive = true;
		down_binding.command = std::make_unique<MoveCameraInputCommand>(0.0f, 5.0f);
	}

	const std::vector<GamepadButtonBinding>& GamepadMapping::GetButtonBindings() const
	{
		return m_button_bindings;
	}

	const std::vector<GamepadJoystickBinding>& GamepadMapping::GetJoystickBindings() const
	{
		return m_joystick_bindings;
	}

	int GamepadMapping::GetDeadZone() const
	{
		return m_deadzone;
	}
}