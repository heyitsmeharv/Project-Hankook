#include "Command.h"
#include "KeyboardMouseMapping.h"
#include "MoveCommand.h"

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
		KeyMouseCommandBinding& binding = m_bindings.emplace_back();
		binding.name = "test";
		binding.keys.push_back(SDL_SCANCODE_W);
		binding.command = std::make_unique<MoveCommand>(1, 1);
	}

	const std::vector<KeyMouseCommandBinding>& KeyboardMouseMapping::GetBindings() const
	{
		return m_bindings;
	}
}