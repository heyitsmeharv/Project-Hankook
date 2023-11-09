#include "GameModel.h"

#include "ConstraintAttachment.h"
#include "Engine.h"
#include "EngineAccess.h"
#include "GamepadInstance.h"
#include "KeyboardMouseInstance.h"
#include "LockOnAttachment.h"
#include "TextureManager.h"

#include "CameraComponent.h"
#include "PlayerControllerComponent.h"
#include "TilemapComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace hk
{
	GameModel::GameModel(Engine& engine)
		: m_engine(engine)
		, m_model_command_queue()
		, m_registry()
		, m_player_entity(entt::null)
		, m_camera_system()
		, m_controller_system()
		, m_rendering_system()
	{
	}

	GameModel::~GameModel()
	{
	}

	void GameModel::Initialise()
	{
		//----- TILE MAP -----
		entt::entity tilemap_entity = m_registry.create();
		TilemapComponent& tilemap = m_registry.emplace<TilemapComponent>(tilemap_entity);
		LoadTilemapFromFile(tilemap, "Data\\Tilemap\\demo_project_2.json");

		//----- PLAYER -----
		m_player_entity = m_registry.create();
		TransformComponent& player_transform = m_registry.emplace<TransformComponent>(m_player_entity);
		player_transform.position = Vector2f{ 100.0f, 100.0f };

		const hk::Texture* texture = &GetEngine().GetTextureManager().GetTexture("Data\\Images\\blank_circle_64.png");
		if (texture)
		{
			SpriteComponent& player_sprite = m_registry.emplace<SpriteComponent>(m_player_entity);
			player_sprite.texture = texture;
			player_sprite.z_index = 1;
		}

		//---- CAMERA -----
		CameraInitInfo camera_init_info;
		camera_init_info.id = "main";
		camera_init_info.position = { 0.0f, 0.0f };
		camera_init_info.dimensions = m_engine.GameWindow().GetWindowDimensions();
		camera_init_info.zoom = 1.0f;

		m_camera_system.PushNewCamera(m_registry, camera_init_info);
		m_camera_system.AddAttachment(m_registry, m_camera_system.CurrentCamera(), std::make_unique<LockOnAttachment>(m_player_entity, hk::Vector2f{ camera_init_info.dimensions.x * 0.5f, camera_init_info.dimensions.y * 0.5f }));
		m_camera_system.AddAttachment(m_registry, m_camera_system.CurrentCamera(), std::make_unique<ConstraintAttachment>(SDL_FRect(0.0f, 0.0f, (float)tilemap.render_dimensions.x, (float)tilemap.render_dimensions.y)));

		//----- CONTROLLER -----
		LoadPlayerController();
	}

	void GameModel::Destroy()
	{
	}

	void GameModel::Update(const double /*delta_time*/)
	{
		m_controller_system.Update(m_registry);
		m_camera_system.Update(m_registry);

		ProcessModelCommands();
		
		m_rendering_system.Update(m_registry, m_camera_system.CurrentCamera());
	}

	void GameModel::ProcessModelCommands()
	{
		m_model_command_queue.ProcessQueue(m_registry);
		m_model_command_queue.ClearQueue();
	}

	bool GameModel::LoadPlayerController()
	{
		std::unique_ptr<ControllerInstance> controller_instance;

		if (m_engine.GetInputDeviceManager().GetGamepadDevices().empty() == false)
		{
			controller_instance = std::make_unique<hk::GamepadInstance>(&m_engine.GetInputDeviceManager().GetGamepadDevices().front());
		}
		else
		{
			controller_instance = std::make_unique<hk::KeyboardMouseInstance>(&m_engine.GetInputDeviceManager().GetDefaultKeyboardMouse());
		}

		entt::entity player_controller_entity = m_registry.create();
		PlayerControllerComponent& player_controller = m_registry.emplace<PlayerControllerComponent>(player_controller_entity);
		player_controller.id = "player_1";
		player_controller.controller = std::move(controller_instance);
		player_controller.is_enabled = true;
		player_controller.controlled_entity = m_player_entity;

		return true;
	}

	void GameModel::QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command)
	{
		m_model_command_queue.AddToQueue(std::move(model_command));
	}

	const entt::registry& GameModel::GetRegistry() const
	{
		return m_registry;
	}
}