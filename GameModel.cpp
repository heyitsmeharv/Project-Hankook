#include "GameModel.h"

#include "CameraManager.h"
#include "Collidable.h"
#include "ConstraintAttachment.h"
#include "Engine.h"
#include "GameObject.h"
#include "GamepadInstance.h"
#include "KeyboardMouseInstance.h"
#include "LockOnAttachment.h"
#include "MoveObjectModelCommand.h"
#include "ProjectileGameObject.h"
#include "PowerUpGameObject.h"
#include "TextureManager.h"
#include "StepResourceModifier.h"

namespace hk
{
	GameModel::GameModel(Engine& engine)
		: m_engine(engine)
		, m_player_controller()
		, m_tilemap()
		, m_root_object(nullptr)
		, m_model_command_queue()
	{
	}

	GameModel::~GameModel()
	{
	}

	void GameModel::Initialise()
	{
		//----- GAME OBJECTS -----
		hk::GameObjectInitInfo parent_object_init_info{ "root", { 0, 0 }, { 1, 1 }, nullptr };
		hk::GameObjectInitInfo child_object_init_info{ "child", { 100, 100 }, { 64, 64 }, &m_engine.GetTextureManager().GetTexture("Data\\Images\\blank_circle_64.png") };
		hk::PowerUpGameObjectInitInfo powerup_init_info{ "powerup", { 110, 100 }, { 64, 64 }, &m_engine.GetTextureManager().GetTexture("Data\\Images\\blank_circle_64.png") };
		hk::ProjectileGameObjectInitInfo proj_init_info{ "proj_1", { 0, 0 }, { 32, 32 }, &m_engine.GetTextureManager().GetTexture("Data\\Images\\blank_circle_64.png"), std::nullopt, { 0.0f, 1.0f }, 1.0, -1.0 };

		m_root_object = std::make_unique<GameObject>( parent_object_init_info );
		m_root_object->AddChild(std::make_unique<hk::GameObject>(child_object_init_info));
		m_root_object->AddChild(std::make_unique<hk::PowerUpGameObject>(powerup_init_info));
		m_root_object->AddChild(std::make_unique<hk::ProjectileGameObject>(proj_init_info));

		m_root_object->AddCollidable(Collidable{ Circle{ { 0.0f, 0.0f }, 5.0f } });
		for (auto& child : m_root_object->GetChildren())
		{
			child->AddCollidable(Collidable{ Circle{ { 0.0f, 0.0f }, 10.0f } });
		}

		hk::GameObject::SetRootObject(*m_root_object);

		StepResourceModifierInitInfo step_modifier_info;
		step_modifier_info.id = "test_decay";
		step_modifier_info.modifier_amount = -20.0;
		step_modifier_info.modifier_rate = 0.5;
		m_root_object->AddHealthModifier(new StepResourceModifier(step_modifier_info));

		//----- TILE MAP -----
		m_tilemap.Load("Data\\Tilemap\\demo_project.json");

		//----- CONTROLLER -----
		LoadPlayerController();
		m_player_controller.AttachGameObject(*m_root_object->GetChildren().front().get());

		Camera* camera = m_engine.GetCameraManager().CurrentCamera();
		if (camera)
		{
			m_player_controller.AttachCamera(*camera);

			//----- CAMERA ATTACHMENTS -----
			//camera->AddAttachment(std::make_unique<hk::LockOnAttachment>(*m_root_object->GetChildren().front().get(), hk::Vector2f{ camera->GetDimensions().x * 0.5f, camera->GetDimensions().y * 0.5f }));
			camera->AddAttachment(std::make_unique<hk::ConstraintAttachment>(SDL_FRect{ m_tilemap.GetPosition().x, m_tilemap.GetPosition().y, static_cast<float>(m_tilemap.GetDimensions().x), static_cast<float>(m_tilemap.GetDimensions().y) }));
		}
	}

	void GameModel::Destroy()
	{
	}

	void GameModel::Update(const double delta_time)
	{
		m_player_controller.Update();
		ProcessModelCommands();

		if (m_root_object)
		{
			m_root_object->Update(delta_time);
		}

	}

	void GameModel::ProcessModelCommands()
	{
		m_model_command_queue.ProcessQueue();
		m_model_command_queue.ClearQueue();
	}

	void GameModel::Draw() const
	{
		m_tilemap.Draw();

		if (m_root_object)
		{
			m_root_object->Draw();
		}
	}

	bool GameModel::LoadPlayerController()
	{
		if (m_engine.GetInputDeviceManager().GetGamepadDevices().empty() == false)
		{
			std::unique_ptr<hk::GamepadInstance> gamepad_instance = std::make_unique<hk::GamepadInstance>();
			gamepad_instance->AttachDevice(m_engine.GetInputDeviceManager().GetGamepadDevices().front());

			m_player_controller.AttachControllerInstance(std::move(gamepad_instance));
		}
		else
		{
			std::unique_ptr<hk::KeyboardMouseInstance> keyboard_instance = std::make_unique<hk::KeyboardMouseInstance>();
			keyboard_instance->AttachDevice(m_engine.GetInputDeviceManager().GetDefaultKeyboardMouse());

			m_player_controller.AttachControllerInstance(std::move(keyboard_instance));
		}

		return true;
	}

	void GameModel::QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command)
	{
		m_model_command_queue.AddToQueue(std::move(model_command));
	}
}