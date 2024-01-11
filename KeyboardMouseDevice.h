#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>

#include <optional>
#include <unordered_map>
#include "Vector2.h"

namespace hk
{
	struct KeyInputData
	{
		double time_held = 0.0;
	};

	struct MouseInputData 
	{
		double time_held = 0.0;
		Vector2i click_pos;
	};

	struct WheelEvent
	{
		Uint32	mouse_id;
		float	x_delta;
		float	y_delta;
	};

	struct DragEvent
	{
		Vector2i start_pos;
		Vector2i end_pos;
		Vector2i pos_delta;
		double	 time_dragging;
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

		const std::unordered_map<SDL_KeyCode, KeyInputData>&	GetKeysDown			() const;
		const std::unordered_map<Uint8, MouseInputData>&		GetMouseButtonsDown	() const;
		const std::optional<WheelEvent>&						GetWheelEvent		() const;
		const std::optional<DragEvent>&							GetDragEvent		() const;

	private:
		std::unordered_map<SDL_KeyCode, KeyInputData>	m_keys_down;
		std::unordered_map<Uint8, MouseInputData>		m_mouse_buttons_down;
		std::optional<WheelEvent>						m_wheel_event;
		std::optional<DragEvent>						m_drag_event;
	};
}