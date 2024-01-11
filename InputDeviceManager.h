#pragma once

#include <vector>

#include "KeyboardMouseDevice.h"
#include "GamepadDevice.h"

namespace hk
{
	class KeyboardMouseDevice;
	class GamepadDevice;

	class InputDeviceManager final
	{
	public:
		void LoadKeyboardMouse	();
		void LoadGamepads		();

		void NewTick			();
		void Update				(const double dt);
		void ProcessEvent		(SDL_Event& event);

		const KeyboardMouseDevice&			GetDefaultKeyboardMouse() const;
		
		const std::vector<GamepadDevice>&	GetGamepadDevices() const;
		const GamepadDevice*				GetGamepadDevice(const SDL_JoystickID joystick_id) const;

	private:
		std::vector<KeyboardMouseDevice>	m_keyboard_mouse_devices;
		std::vector<GamepadDevice>			m_gamepad_devices;
	};
}