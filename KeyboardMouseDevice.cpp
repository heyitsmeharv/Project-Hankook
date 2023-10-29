#include "KeyboardMouseDevice.h"

#include <algorithm>

namespace hk
{
	void KeyboardMouseDevice::NewTick()
	{
		m_wheel_event = std::nullopt;
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
			m_keys_down.emplace((SDL_KeyCode)event.key.keysym.sym, InputData {});
		}
		else if (event.type == SDL_KEYUP)
		{
			m_keys_down.erase((SDL_KeyCode)event.key.keysym.sym);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			m_mouse_buttons_down.emplace(event.button.button, InputData {});
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			m_mouse_buttons_down.erase(event.button.button);
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

	const std::unordered_map<SDL_KeyCode, InputData>& KeyboardMouseDevice::GetKeysDown() const
	{
		return m_keys_down;
	}

	const std::unordered_map<Uint8, InputData>& KeyboardMouseDevice::GetMouseButtonsDown() const
	{
		return m_mouse_buttons_down;
	}

	const std::optional<WheelEvent>& KeyboardMouseDevice::GetWheelEvent() const
	{
		return m_wheel_event;
	}
}