#include "GamepadDevice.h"
#include "ErrorManager.h"

namespace hk
{
	GamepadDevice::GamepadDevice(const int sdl_device_index)
		: m_game_controller(nullptr)
	{
		Initialise(sdl_device_index);
	}

	GamepadDevice::~GamepadDevice()
	{
		Close();
	}

	void GamepadDevice::Initialise(const int sdl_device_index)
	{
		m_game_controller = SDL_GameControllerOpen(sdl_device_index);
		if (SDL_GameControllerHasRumble(m_game_controller) == false)
		{
			hk::Warn(hk::ErrorCategory::INPUT, "Game controller at index %d does not support rumble", sdl_device_index);
		}
	}

	void GamepadDevice::Update(const double dt)
	{

	}

	void GamepadDevice::ProcessEvent(SDL_Event& event)
	{
		
	}

	void GamepadDevice::Close()
	{
		if (m_game_controller)
		{
			SDL_GameControllerClose(m_game_controller);
		}
	}

	bool GamepadDevice::IsButtonPressed(const SDL_GameControllerButton button) const
	{
		return SDL_GameControllerGetButton(m_game_controller, button) != 0;
	}

	Sint16 GamepadDevice::GetJoystickDelta(const SDL_GameControllerAxis axis) const
	{
		return SDL_GameControllerGetAxis(m_game_controller, axis);
	}

	SDL_JoystickID GamepadDevice::GetJoystickID() const
	{
		return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_game_controller));
	}
}