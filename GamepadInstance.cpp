#include "InputCommand.h"
#include "GamepadInstance.h"
#include "GamepadDevice.h"

namespace hk
{
	GamepadInstance::GamepadInstance()
		: m_device(nullptr)
	{
	}

	GamepadInstance::~GamepadInstance()
	{
		m_device = nullptr;
	}

	std::vector<std::unique_ptr<InputCommand>> GamepadInstance::Update() const
	{
		std::vector<std::unique_ptr<InputCommand>> commands;

		if (m_device)
		{
			for (const auto& binding : m_mapping.GetBindings())
			{
				if (binding.button != SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID)
				{
					if (m_device->IsButtonPressed(binding.button))
					{
						commands.push_back(binding.command->Clone());
					}
				}
				else if (binding.joystick_axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID)
				{
					if (std::abs(m_device->GetJoystickDelta(binding.joystick_axis)) > m_mapping.GetDeadZone())
					{
						commands.push_back(binding.command->Clone());
					}
				}
			}
		}

		return commands;
	}

	void GamepadInstance::AttachDevice(const GamepadDevice& device)
	{
		m_device = &device;
	}
}