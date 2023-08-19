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
			for (const auto& binding : m_mapping.GetButtonBindings())
			{
				if (binding.button != SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID)
				{
					if (m_device->IsButtonPressed(binding.button))
					{
						commands.push_back(binding.command->Clone());
					}
				}
			}

			// This code is probably more verbose than it should be due to lots of duplication
			// However, it's so much easier to debug and understand this way that I'm going to allow it
			for (const auto& binding : m_mapping.GetJoystickBindings())
			{
				if (binding.joystick_axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID)
				{
					const Sint16 stick_delta = m_device->GetJoystickDelta(binding.joystick_axis);

					if (binding.is_positive)
					{
						if (stick_delta > m_mapping.GetDeadZone())
						{
							DeviceInputInfo info;
							info.press_modifier = (float)stick_delta / std::numeric_limits<Sint16>::max();

							std::unique_ptr<InputCommand> new_command = binding.command->Clone();
							new_command->ConfigureFromDeviceInput(info);
							commands.push_back(std::move(new_command));
						}
					}
					else
					{
						if (stick_delta < -m_mapping.GetDeadZone())
						{
							DeviceInputInfo info;
							info.press_modifier = (float)stick_delta / std::numeric_limits<Sint16>::min();

							std::unique_ptr<InputCommand> new_command = binding.command->Clone();
							new_command->ConfigureFromDeviceInput(info);
							commands.push_back(std::move(new_command));
						}
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