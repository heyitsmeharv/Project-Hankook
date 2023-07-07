#include "Command.h"
#include "KeyboardMouseMapping.h"
#include "MoveCommand.h"

namespace hk
{
	KeyboardMouseMapping::KeyboardMouseMapping()
	{
		KeyMouseCommandBinding& binding = m_bindings.emplace_back();
		binding.name = "test";
		binding.keys.push_back(SDL_SCANCODE_W);
		binding.command = std::make_unique<MoveCommand>(5.0f, 5.0f);
	}

	const std::vector<KeyMouseCommandBinding>& KeyboardMouseMapping::GetBindings() const
	{
		return m_bindings;
	}
}