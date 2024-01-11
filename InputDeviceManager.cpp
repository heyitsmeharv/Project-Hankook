#include "InputDeviceManager.h"

namespace hk
{
	void InputDeviceManager::NewTick()
	{
		for (auto& km_device : m_keyboard_mouse_devices)
		{
			km_device.NewTick();
		}
	}

	void InputDeviceManager::Update(const double dt)
	{
		for (auto& km_device : m_keyboard_mouse_devices)
		{
			km_device.Update(dt);
		}

		for (auto& gamepad : m_gamepad_devices)
		{
			gamepad.Update(dt);
		}
	}

	void InputDeviceManager::ProcessEvent(SDL_Event& event)
	{
		for (auto& km_device : m_keyboard_mouse_devices)
		{
			km_device.ProcessEvent(event);
		}

		for (auto& gamepad : m_gamepad_devices)
		{
			gamepad.ProcessEvent(event);
		}
	}

	void InputDeviceManager::LoadKeyboardMouse()
	{
		m_keyboard_mouse_devices.emplace_back();
	}

	void InputDeviceManager::LoadGamepads()
	{
		for (int index = 0; index < SDL_NumJoysticks(); index++)
		{
			if (SDL_IsGameController(index))
			{
				m_gamepad_devices.emplace_back(index);
			}
		}
	}

	const KeyboardMouseDevice& InputDeviceManager::GetDefaultKeyboardMouse() const
	{
		return m_keyboard_mouse_devices.front();
	}

	const std::vector<GamepadDevice>& InputDeviceManager::GetGamepadDevices() const
	{
		return m_gamepad_devices;
	}

	const GamepadDevice* InputDeviceManager::GetGamepadDevice(const SDL_JoystickID joystick_id) const
	{
		const auto itr = std::find_if(m_gamepad_devices.begin(), m_gamepad_devices.end(), [&joystick_id](const GamepadDevice& gamepad) { return gamepad.GetJoystickID() == joystick_id; });
		if (itr != m_gamepad_devices.end())
		{
			return &(*itr);
		}

		return nullptr;
	}
}