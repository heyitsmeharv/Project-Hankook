#include "InputCommand.h"
#include "KeyboardMouseMapping.h"
#include "MoveEntityInputCommand.h"
#include "ZoomCameraInputCommand.h"

namespace hk
{
	InputCommandBinding::InputCommandBinding()
		: name()
		, default_command(nullptr)
	{
	}
	
	InputCommandBinding::~InputCommandBinding()
	{
	}

	InputCommandBinding::InputCommandBinding(InputCommandBinding&& rhs)
	{
		name = rhs.name;
		default_command = std::move(rhs.default_command);
		mod_overrides = std::move(rhs.mod_overrides);
	}

	InputCommandBinding& InputCommandBinding::operator=(InputCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		default_command = std::move(rhs.default_command);
		mod_overrides = std::move(rhs.mod_overrides);

		return *this;
	}

	KeyboardMouseMapping::KeyboardMouseMapping()
	{
		//CHARACTER
		InputCommandBinding w_binding;
		w_binding.name = "w";
		w_binding.default_command = std::make_unique<MoveEntityInputCommand>(0.0f, -5.0f);
		m_key_bindings.insert({ SDLK_w, std::move(w_binding) });

		InputCommandBinding s_binding;
		s_binding.name = "s";
		s_binding.default_command = std::make_unique<MoveEntityInputCommand>(0.0f, 5.0f);
		m_key_bindings.insert({ SDLK_s, std::move(s_binding) });

		InputCommandBinding a_binding;
		a_binding.name = "a";
		a_binding.default_command = std::make_unique<MoveEntityInputCommand>(-5.0f, 0.0f);
		m_key_bindings.insert({ SDLK_a, std::move(a_binding) });

		InputCommandBinding d_binding;
		d_binding.name = "d";
		d_binding.default_command = std::make_unique<MoveEntityInputCommand>(5.0f, 0.0f);
		m_key_bindings.insert({ SDLK_d, std::move(d_binding) });

		// CAMERA
		InputCommandBinding camera_move_up_binding;
		camera_move_up_binding.name = "camera_move_up";
		camera_move_up_binding.default_command = std::make_unique<MoveEntityInputCommand>(0.0f, -5.0f);
		m_key_bindings.insert({ SDLK_UP, std::move(camera_move_up_binding) });

		InputCommandBinding camera_move_down_binding;
		camera_move_down_binding.name = "camera_move_down";
		camera_move_down_binding.default_command = std::make_unique<MoveEntityInputCommand>(0.0f, 5.0f);
		m_key_bindings.insert({ SDLK_DOWN, std::move(camera_move_down_binding) });

		InputCommandBinding camera_move_left_binding;
		camera_move_left_binding.name = "camera_move_left";
		camera_move_left_binding.default_command = std::make_unique<MoveEntityInputCommand>(-5.0f, 0.0f);
		m_key_bindings.insert({ SDLK_LEFT, std::move(camera_move_left_binding) });

		InputCommandBinding camera_move_right_binding;
		camera_move_right_binding.name = "camera_move_right";
		camera_move_right_binding.default_command = std::make_unique<MoveEntityInputCommand>(5.0f, 0.0f);
		m_key_bindings.insert({ SDLK_RIGHT, std::move(camera_move_right_binding) });

		InputCommandBinding camera_zoom_in_binding;
		camera_zoom_in_binding.name = "camera_zoom_in";
		camera_zoom_in_binding.default_command = std::make_unique<ZoomCameraInputCommand>(0.25f);
		m_wheel_bindings.insert({ MouseWheelID::WHEEL_UP, std::move(camera_zoom_in_binding) });
		
		InputCommandBinding camera_zoom_out_binding;
		camera_zoom_out_binding.name = "camera_zoom_out";
		camera_zoom_out_binding.default_command = std::make_unique<ZoomCameraInputCommand>(-0.25f);
		m_wheel_bindings.insert({ MouseWheelID::WHEEL_DOWN, std::move(camera_zoom_out_binding) });

		// GUN
		//InputCommandBinding shoot_binding;
		//shoot_binding.name = "shoot";
		//shoot_binding.default_command = std::make_unique<ShootGunInputCommand>();
		//m_key_bindings.insert({ SDLK_SPACE, std::move(shoot_binding) });
	}

	const InputCommandBinding* KeyboardMouseMapping::GetKeyBinding(const SDL_KeyCode key_code) const
	{
		const auto& itr = m_key_bindings.find(key_code);
		return itr != m_key_bindings.end() ? &itr->second : nullptr;
	}

	const InputCommandBinding* KeyboardMouseMapping::GetMouseButtonBinding(const Uint8 mouse_button) const
	{
		const auto& itr = m_mouse_bindings.find(mouse_button);
		return itr != m_mouse_bindings.end() ? &itr->second : nullptr;
	}

	const InputCommandBinding* KeyboardMouseMapping::GetWheelBinding(const MouseWheelID wheel_id) const
	{
		const auto& itr = m_wheel_bindings.find(wheel_id);
		return itr != m_wheel_bindings.end() ? &itr->second : nullptr;
	}
}