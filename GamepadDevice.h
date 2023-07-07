#pragma once

#include <SDL_gamecontroller.h>
#include <SDL_haptic.h>
#include "Vector2.h"

namespace hk
{
	class GamepadDevice final
	{
	public:
		 GamepadDevice(const int sdl_device_index);
		~GamepadDevice();

		void Initialise(const int sdl_device_index);
		void Close();

		bool	IsButtonPressed	(const SDL_GameControllerButton button) const;
		Sint16	GetJoystickDelta(const SDL_GameControllerAxis axis) const;

		SDL_JoystickID GetJoystickID() const;

	private:
		SDL_GameController* m_game_controller;
	};
}