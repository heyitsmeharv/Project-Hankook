#include "InputCommand.h"
#include "KeyboardMouseMapping.h"
#include "MoveCameraInputCommand.h"
#include "MoveObjectInputCommand.h"
#include "ShootGunInputCommand.h"

namespace hk
{
	KeyMouseCommandBinding::KeyMouseCommandBinding()
		: name()
		, keys()
		, mouse_buttons()
		, command(nullptr)
	{
	}
	
	KeyMouseCommandBinding::~KeyMouseCommandBinding()
	{
	}

	KeyMouseCommandBinding::KeyMouseCommandBinding(KeyMouseCommandBinding&& rhs)
	{
		name = rhs.name;
		keys = rhs.keys;
		mouse_buttons = rhs.mouse_buttons;
		command = std::move(rhs.command);
	}

	KeyMouseCommandBinding& KeyMouseCommandBinding::operator=(KeyMouseCommandBinding&& rhs)
	{
		name = std::move(rhs.name);
		keys = std::move(rhs.keys);
		mouse_buttons = std::move(rhs.mouse_buttons);
		command = std::move(rhs.command);
		return *this;
	}

	KeyboardMouseMapping::KeyboardMouseMapping()
	{
		//CHARACTER
		KeyMouseCommandBinding& w_binding = m_bindings.emplace_back();
		w_binding.name = "w";
		w_binding.keys.push_back(SDL_SCANCODE_W);
		w_binding.command = std::make_unique<MoveObjectInputCommand>(0.0f, -5.0f);

		KeyMouseCommandBinding& s_binding = m_bindings.emplace_back();
		s_binding.name = "s";
		s_binding.keys.push_back(SDL_SCANCODE_S);
		s_binding.command = std::make_unique<MoveObjectInputCommand>(0.0f, 5.0f);

		KeyMouseCommandBinding& a_binding = m_bindings.emplace_back();
		a_binding.name = "a";
		a_binding.keys.push_back(SDL_SCANCODE_A);
		a_binding.command = std::make_unique<MoveObjectInputCommand>(-5.0f, 0.0f);

		KeyMouseCommandBinding& d_binding = m_bindings.emplace_back();
		d_binding.name = "d";
		d_binding.keys.push_back(SDL_SCANCODE_D);
		d_binding.command = std::make_unique<MoveObjectInputCommand>(5.0f, 0.0f);

		// CAMERA
		KeyMouseCommandBinding& camera_move_up_binding = m_bindings.emplace_back();
		camera_move_up_binding.name = "camera_move_up";
		camera_move_up_binding.keys.push_back(SDL_SCANCODE_UP);
		camera_move_up_binding.command = std::make_unique<MoveCameraInputCommand>(0.0f, -5.0f);

		KeyMouseCommandBinding& camera_move_down_binding = m_bindings.emplace_back();
		camera_move_down_binding.name = "camera_move_down";
		camera_move_down_binding.keys.push_back(SDL_SCANCODE_DOWN);
		camera_move_down_binding.command = std::make_unique<MoveCameraInputCommand>(0.0f, 5.0f);

		KeyMouseCommandBinding& camera_move_left_binding = m_bindings.emplace_back();
		camera_move_left_binding.name = "camera_move_left";
		camera_move_left_binding.keys.push_back(SDL_SCANCODE_LEFT);
		camera_move_left_binding.command = std::make_unique<MoveCameraInputCommand>(-5.0f, 0.0f);

		KeyMouseCommandBinding& camera_move_right_binding = m_bindings.emplace_back();
		camera_move_right_binding.name = "camera_move_right";
		camera_move_right_binding.keys.push_back(SDL_SCANCODE_RIGHT);
		camera_move_right_binding.command = std::make_unique<MoveCameraInputCommand>(5.0f, 0.0f);

		// GUN
		KeyMouseCommandBinding& shoot_binding = m_bindings.emplace_back();
		shoot_binding.name = "shoot";
		shoot_binding.keys.push_back(SDL_SCANCODE_SPACE);
		shoot_binding.command = std::make_unique<ShootGunInputCommand>();
	}

	const std::vector<KeyMouseCommandBinding>& KeyboardMouseMapping::GetBindings() const
	{
		return m_bindings;
	}
}