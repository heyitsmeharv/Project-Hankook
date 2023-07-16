#include "Command.h"
#include "KeyboardMouseMapping.h"
#include "MoveCommand.h"
#include "ShootGunCommand.h"

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
		KeyMouseCommandBinding& w_binding = m_bindings.emplace_back();
		w_binding.name = "w";
		w_binding.keys.push_back(SDL_SCANCODE_W);
		w_binding.command = std::make_unique<MoveCommand>(0.0f, -1.0f);

		KeyMouseCommandBinding& s_binding = m_bindings.emplace_back();
		s_binding.name = "s";
		s_binding.keys.push_back(SDL_SCANCODE_S);
		s_binding.command = std::make_unique<MoveCommand>(0.0f, 1.0f);

		KeyMouseCommandBinding& a_binding = m_bindings.emplace_back();
		a_binding.name = "a";
		a_binding.keys.push_back(SDL_SCANCODE_A);
		a_binding.command = std::make_unique<MoveCommand>(-1.0f, 0.0f);

		KeyMouseCommandBinding& d_binding = m_bindings.emplace_back();
		d_binding.name = "d";
		d_binding.keys.push_back(SDL_SCANCODE_D);
		d_binding.command = std::make_unique<MoveCommand>(1.0f, 0.0f);

		KeyMouseCommandBinding& shoot_binding = m_bindings.emplace_back();
		shoot_binding.name = "d";
		shoot_binding.keys.push_back(SDL_SCANCODE_SPACE);
		shoot_binding.command = std::make_unique<ShootGunCommand>();
	}

	const std::vector<KeyMouseCommandBinding>& KeyboardMouseMapping::GetBindings() const
	{
		return m_bindings;
	}
}