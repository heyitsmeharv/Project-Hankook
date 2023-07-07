#include "Command.h"
#include "PlayerController.h"
#include "ControllerInstance.h"

namespace
{
	int GenerateID()
	{
		static int current_id = 0;
		return current_id++;
	}
}

namespace hk
{
	PlayerController::PlayerController()
		: m_id(GenerateID())
		, m_game_object(nullptr)
		, m_is_disabled(false)
		, m_controller_instance(nullptr)
	{
	}

	PlayerController::PlayerController(GameObject* game_object)
		: m_id(GenerateID())
		, m_game_object(game_object)
		, m_is_disabled(false)
		, m_controller_instance(nullptr)
	{
	}

	PlayerController::~PlayerController()
	{
		m_game_object = nullptr;
	}

	void PlayerController::OnInputChange() const
	{
		std::vector<std::unique_ptr<Command>> command_list = m_controller_instance->HandleInput();
		for (auto& command : command_list)
		{
			command->Execute();
		}
	}

	void PlayerController::AttachGameObject(GameObject* game_object)
	{
		m_game_object = game_object;
	}

	void PlayerController::AttachControllerInstance(std::unique_ptr<ControllerInstance>&& controller_instance)
	{
		m_controller_instance = std::move(controller_instance);
	}

	void PlayerController::SetDisabled(const bool is_disabled)
	{
		m_is_disabled = is_disabled;
	}

	bool PlayerController::IsDisabled() const
	{
		return m_is_disabled;
	}
}