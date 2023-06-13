#include "KeyboardInputHandler.h"
#include "Command.h"
#include "MoveCommand.h"

#include <algorithm>

namespace hk
{
	KeyboardInputHandler::KeyboardInputHandler()
	{
		m_key_bindings = 
		{
			{ "test_binding", { SDL_SCANCODE_W }, new MoveCommand(5.0f, 5.0f) }
		};
	}

	KeyboardInputHandler::~KeyboardInputHandler()
	{
		Destroy();
	}

	void KeyboardInputHandler::Destroy()
	{
		for (auto& key_bind : m_key_bindings)
		{
			delete key_bind.command;
			key_bind.command = nullptr;
		}
	}

	void KeyboardInputHandler::Update(const SDL_Event&)
	{
		const Uint8* key_states = SDL_GetKeyboardState(nullptr);

		for (const auto& key_bind : m_key_bindings)
		{
			const bool is_all_pressed = std::all_of(key_bind.keys.begin(), key_bind.keys.end(), [&key_states](const SDL_Scancode scan_code) 
			{
				return key_states[scan_code];
			});

			if (is_all_pressed && key_bind.command)
			{
				key_bind.command->Execute();
				break;
			}
		}
	}
}