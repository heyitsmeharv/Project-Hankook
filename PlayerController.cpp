#include "InputCommand.h"
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
		, m_camera(nullptr)
		, m_is_disabled(false)
		, m_controller_instance(nullptr)
	{
	}

	PlayerController::PlayerController(GameObject& game_object, Camera* camera)
		: m_id(GenerateID())
		, m_game_object(&game_object)
		, m_camera(camera)
		, m_is_disabled(false)
		, m_controller_instance(nullptr)
	{
	}

	PlayerController::~PlayerController()
	{
		m_camera = nullptr;
		m_game_object = nullptr;
	}

	void PlayerController::Update() const
	{
		if (m_game_object)
		{
			std::vector<std::unique_ptr<InputCommand>> command_list = m_controller_instance->Update();
			for (auto& command : command_list)
			{
				command->Execute(*m_game_object, m_camera);
			}
		}
	}

	void PlayerController::AttachGameObject(GameObject& game_object)
	{
		m_game_object = &game_object;
	}

	void PlayerController::AttachCamera(Camera& camera)
	{
		m_camera = &camera;
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