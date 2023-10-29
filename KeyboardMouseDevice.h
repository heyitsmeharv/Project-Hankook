#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>

#include <optional>
#include <unordered_map>

namespace hk
{
	struct InputData
	{
		double		time_held = 0.0;
	};

	struct WheelEvent
	{
		Uint32	mouse_id;
		float	x_delta;
		float	y_delta;
	};

	class KeyboardMouseDevice
	{
	public:
		void	NewTick			();
		void	Update			(const double dt);
		void	ProcessEvent	(SDL_Event& event);

		bool	IsModPressed	(const SDL_Keymod) const;

		bool	IsKeyPressed	(const SDL_KeyCode keycode) const;
		double	KeyHeldTime		(const SDL_KeyCode keycode) const;

		bool	IsMouseButtonPressed(const Uint8 mouse_button) const;
		double	MouseButtonHeldTime	(const Uint8 mouse_button) const;

		const std::unordered_map<SDL_KeyCode, InputData>&	GetKeysDown			() const;
		const std::unordered_map<Uint8, InputData>&			GetMouseButtonsDown	() const;
		const std::optional<WheelEvent>&					GetWheelEvent		() const;

	private:
		std::unordered_map<SDL_KeyCode, InputData>	m_keys_down;
		std::unordered_map<Uint8, InputData>		m_mouse_buttons_down;
		std::optional<WheelEvent>					m_wheel_event;
	};
}