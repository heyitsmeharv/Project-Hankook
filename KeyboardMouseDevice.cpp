#include "KeyboardMouseDevice.h"

#include <algorithm>

namespace hk
{
	void KeyboardMouseDevice::NewTick()
	{
		m_wheel_event = std::nullopt;
		m_drag_event = std::nullopt;
	}

	void KeyboardMouseDevice::Update(const double dt)
	{
		//Should only be a few keys so map should still be okay
		for (auto& [keycode, data] : m_keys_down)
		{
			data.time_held += dt;
		}

		for (auto& [mouse_button, data] : m_mouse_buttons_down)
		{
			data.time_held += dt;
		}
	}

	void KeyboardMouseDevice::ProcessEvent(SDL_Event& event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			m_keys_down.emplace((SDL_KeyCode)event.key.keysym.sym, KeyInputData{});
		}
		else if (event.type == SDL_KEYUP)
		{
			m_keys_down.erase((SDL_KeyCode)event.key.keysym.sym);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			m_mouse_buttons_down.emplace(event.button.button, MouseInputData { 0.0, Vector2i{ event.button.x, event.button.y }});
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			//Look for the already existing button down event
			const auto& itr = m_mouse_buttons_down.find(event.button.button);
			if (itr != m_mouse_buttons_down.end())
			{
				//If the mouse pos is different, it means we've had a drag
				const Vector2i end_pos{ event.button.x, event.button.y };
				if (itr->second.click_pos != end_pos)
				{
					//So, lets create the drag event
					m_drag_event = DragEvent{};
					m_drag_event->start_pos = itr->second.click_pos;
					m_drag_event->end_pos = end_pos;
					m_drag_event->pos_delta = m_drag_event->end_pos - m_drag_event->start_pos;
					m_drag_event->time_dragging = itr->second.time_held;
				}

				//Erase the down event as the button is no longer down
				m_mouse_buttons_down.erase(event.button.button);
			}
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			const bool should_flip = event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED;

			m_wheel_event = WheelEvent{};
			m_wheel_event->mouse_id = event.wheel.which;
			m_wheel_event->x_delta = should_flip ? event.wheel.preciseY : event.wheel.preciseX;
			m_wheel_event->y_delta = should_flip ? event.wheel.preciseX : event.wheel.preciseY;
		}
	}

	bool KeyboardMouseDevice::IsKeyPressed(const SDL_KeyCode keycode) const
	{
		return m_keys_down.find(keycode) != m_keys_down.end();
	}

	double KeyboardMouseDevice::KeyHeldTime(const SDL_KeyCode keycode) const
	{
		const auto& itr = m_keys_down.find(keycode);
		return itr != m_keys_down.end() ? itr->second.time_held : -1.0;
	}

	bool KeyboardMouseDevice::IsMouseButtonPressed(const Uint8 mouse_button) const
	{
		return m_mouse_buttons_down.find(mouse_button) != m_mouse_buttons_down.end();
	}

	double KeyboardMouseDevice::MouseButtonHeldTime(const Uint8 mouse_button) const
	{
		const auto& itr = m_mouse_buttons_down.find(mouse_button);
		return itr != m_mouse_buttons_down.end() ? itr->second.time_held : -1.0;
	}

	bool KeyboardMouseDevice::IsModPressed(const SDL_Keymod mod_key) const
	{
		return (SDL_GetModState() & mod_key) > 0;
	}

	const std::unordered_map<SDL_KeyCode, KeyInputData>& KeyboardMouseDevice::GetKeysDown() const
	{
		return m_keys_down;
	}

	const std::unordered_map<Uint8, MouseInputData>& KeyboardMouseDevice::GetMouseButtonsDown() const
	{
		return m_mouse_buttons_down;
	}

	const std::optional<WheelEvent>& KeyboardMouseDevice::GetWheelEvent() const
	{
		return m_wheel_event;
	}

	const std::optional<DragEvent>& KeyboardMouseDevice::GetDragEvent() const
	{
		return m_drag_event;
	}
}