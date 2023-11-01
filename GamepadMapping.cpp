#include "InputCommand.h"
#include "GamepadMapping.h"
#include "MoveEntityInputCommand.h"

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
		//BUTTONS
		GamepadButtonBinding& button_binding = m_button_bindings.emplace_back();
		button_binding.name = "button_test";
		button_binding.button = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		button_binding.command = std::make_unique<MoveEntityInputCommand>(5.0f, 5.0f);
		
		//LEFT STICK
		GamepadJoystickBinding& player_right_binding = m_joystick_bindings.emplace_back();
		player_right_binding.name = "player_right";
		player_right_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		player_right_binding.is_positive = true;
		player_right_binding.command = std::make_unique<MoveEntityInputCommand>(2.0f, 0.0f);

		GamepadJoystickBinding& player_left_binding = m_joystick_bindings.emplace_back();
		player_left_binding.name = "player_left";
		player_left_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		player_left_binding.is_positive = false;
		player_left_binding.command = std::make_unique<MoveEntityInputCommand>(-2.0f, 0.0f);

		GamepadJoystickBinding& player_up_binding = m_joystick_bindings.emplace_back();
		player_up_binding.name = "player_up";
		player_up_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		player_up_binding.is_positive = false;
		player_up_binding.command = std::make_unique<MoveEntityInputCommand>(0.0f, -2.0f);

		GamepadJoystickBinding& player_down_binding = m_joystick_bindings.emplace_back();
		player_down_binding.name = "player_down";
		player_down_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		player_down_binding.is_positive = true;
		player_down_binding.command = std::make_unique<MoveEntityInputCommand>(0.0f, 2.0f);

		//RIGHT STICK
		GamepadJoystickBinding& camera_right_binding = m_joystick_bindings.emplace_back();
		camera_right_binding.name = "camera_right";
		camera_right_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;
		camera_right_binding.is_positive = true;
		camera_right_binding.command = std::make_unique<MoveEntityInputCommand>(5.0f, 0.0f);
		
		GamepadJoystickBinding& camera_left_binding = m_joystick_bindings.emplace_back();
		camera_left_binding.name = "camera_left";
		camera_left_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;
		camera_left_binding.is_positive = false;
		camera_left_binding.command = std::make_unique<MoveEntityInputCommand>(-5.0f, 0.0f);

		GamepadJoystickBinding& camera_up_binding = m_joystick_bindings.emplace_back();
		camera_up_binding.name = "camera_up";
		camera_up_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;
		camera_up_binding.is_positive = false;
		camera_up_binding.command = std::make_unique<MoveEntityInputCommand>(0.0f, -5.0f);

		GamepadJoystickBinding& camera_down_binding = m_joystick_bindings.emplace_back();
		camera_down_binding.name = "camera_down";
		camera_down_binding.joystick_axis = SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;
		camera_down_binding.is_positive = true;
		camera_down_binding.command = std::make_unique<MoveEntityInputCommand>(0.0f, 5.0f);
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