#pragma once

#include <SDL_keycode.h>
#include <SDL_keyboard.h>
#include <SDL_events.h>

#include <vector>
#include <string>
#include <memory>

namespace hk
{
	class Command;

	struct KeybindingData
	{
		std::string					name;
		std::vector<SDL_Scancode>	keys;
		Command*					command = nullptr;
	};

	class KeyboardInputHandler
	{
	public:
		 KeyboardInputHandler();
		~KeyboardInputHandler();

		void Destroy();

		void Update(const SDL_Event& event);

	private:
		std::vector<KeybindingData> m_key_bindings;

	};
}