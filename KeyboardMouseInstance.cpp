#include "InputCommand.h"
#include "KeyboardMouseInstance.h"
#include "KeyboardMouseDevice.h"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>

namespace hk
{
	KeyboardMouseInstance::KeyboardMouseInstance()
		: m_device(nullptr)
	{
	}

	KeyboardMouseInstance::~KeyboardMouseInstance()
	{
		m_device = nullptr;
	}

	std::vector<std::unique_ptr<InputCommand>> KeyboardMouseInstance::Update() const
	{
		std::vector<std::unique_ptr<InputCommand>> commands;

		if (m_device)
		{
			//Pressed keys
			for (const auto& [key_code, _] : m_device->GetKeysDown())
			{
				const InputCommandBinding* binding = m_mapping.GetKeyBinding(key_code);
				if (binding)
				{
					commands.push_back(GetCommandFromBinding(*binding));
				}
			}

			//Pressed Mouse Buttons
			for (const auto& [mouse_button, _] : m_device->GetMouseButtonsDown())
			{
				const InputCommandBinding* binding = m_mapping.GetMouseButtonBinding(mouse_button);
				if (binding)
				{
					commands.push_back(GetCommandFromBinding(*binding));
				}
			}

			if (m_device->GetWheelEvent())
			{
				const WheelEvent& wheel_event = *m_device->GetWheelEvent();

				const InputCommandBinding* x_binding = nullptr;
				const InputCommandBinding* y_binding = nullptr;

				if (wheel_event.x_delta > 0)
				{
					x_binding = m_mapping.GetWheelBinding(MouseWheelID::WHEEL_RIGHT);
				}
				else if (wheel_event.x_delta < 0)
				{
					x_binding = m_mapping.GetWheelBinding(MouseWheelID::WHEEL_LEFT);
				}

				if (x_binding)
				{
					commands.push_back(GetCommandFromBinding(*x_binding));
				}

				if (wheel_event.y_delta > 0)
				{
					y_binding = m_mapping.GetWheelBinding(MouseWheelID::WHEEL_UP);
				}
				else if (wheel_event.y_delta < 0)
				{
					y_binding = m_mapping.GetWheelBinding(MouseWheelID::WHEEL_DOWN);
				}

				if (y_binding)
				{
					commands.push_back(GetCommandFromBinding(*y_binding));
				}
			}
		}

		return commands;
	}

	std::unique_ptr<InputCommand> KeyboardMouseInstance::GetCommandFromBinding(const InputCommandBinding& binding) const
	{
		//Check if modifier is down
		if (binding.mod_overrides.empty() == false)
		{
			for (const auto& mod_override : binding.mod_overrides)
			{
				if (m_device->IsModPressed(mod_override.mod_key))
				{
					return mod_override.command->Clone();
				}
			}
		}

		return binding.default_command->Clone();
	}

	void KeyboardMouseInstance::AttachDevice(const KeyboardMouseDevice& device)
	{
		m_device = &device;
	}
}