#pragma once

#include <memory>
#include <SDL_scancode.h>
#include <string>
#include <vector>

namespace hk
{
	class Command;

	struct KeyMouseCommandBinding
	{
		 KeyMouseCommandBinding();
		~KeyMouseCommandBinding();

		KeyMouseCommandBinding(KeyMouseCommandBinding&& rhs);
		KeyMouseCommandBinding& operator=(KeyMouseCommandBinding&& rhs);

		KeyMouseCommandBinding(const KeyMouseCommandBinding&) = delete;
		KeyMouseCommandBinding& operator=(const KeyMouseCommandBinding&) = delete;

		std::string					name;
		std::vector<SDL_Scancode>	keys;
		std::vector<Uint32>			mouse_buttons;
		std::unique_ptr<Command>	command;
	};

	class KeyboardMouseMapping final
	{
	public:	
		KeyboardMouseMapping();

		const std::vector<KeyMouseCommandBinding>& GetBindings() const;
	
	private:
		std::vector<KeyMouseCommandBinding> m_bindings;
	};
}