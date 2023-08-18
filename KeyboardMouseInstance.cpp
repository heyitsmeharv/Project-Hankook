#include "InputCommand.h"
#include "KeyboardMouseInstance.h"
#include "KeyboardMouseDevice.h"

#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_events.h>

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
			for (const auto& binding : m_mapping.GetBindings())
			{
				const bool are_all_keys_pressed = binding.keys.empty() || m_device->AreKeysPressed(binding.keys);
				const bool are_all_mouse_buttons_pressed = binding.mouse_buttons.empty() || m_device->AreMouseButtonsPressed(binding.mouse_buttons);
			
				if (are_all_keys_pressed && are_all_mouse_buttons_pressed)
				{
					commands.push_back(binding.command->Clone());
				}
			}
		}

		return commands;
	}

	void KeyboardMouseInstance::AttachDevice(const KeyboardMouseDevice& device)
	{
		m_device = &device;
	}
}