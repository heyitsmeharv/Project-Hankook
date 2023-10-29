#pragma once

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_events.h>
#include "Vector2.h"

namespace hk
{
	class GamepadDevice
	{
	public:
		 GamepadDevice(const int sdl_device_index);
		~GamepadDevice();

		void	Initialise		(const int sdl_device_index);
		void	Close			();

		void	Update			(const double dt);
		void	ProcessEvent	(SDL_Event& event);

		bool	IsButtonPressed	(const SDL_GameControllerButton button) const;
		Sint16	GetJoystickDelta(const SDL_GameControllerAxis axis) const;

		SDL_JoystickID GetJoystickID() const;

	private:
		SDL_GameController* m_game_controller;
	};
}