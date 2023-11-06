#pragma once

#include <memory>
#include <entt/entt.hpp>

#include "CommandQueue.h"
#include "IModel.h"
#include "ModelCommand.h"

#include "CameraSystem.h"
#include "ControllerSystem.h"
#include "RenderingSystem.h"

namespace hk
{
	class CameraManager;
	class Engine;

	class GameModel final : public IModel
	{
	public:
		 GameModel(Engine& engine);
		~GameModel();

		void Initialise	() override;
		void Destroy	() override;
		void Update		(const double delta_time) override;

		void QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command);

		const entt::registry& GetRegistry() const;

	private:
		bool LoadPlayerController();
		void ProcessModelCommands();

	private:
		Engine&							m_engine;

		CommandQueue<ModelCommand>		m_model_command_queue;
		entt::registry					m_registry;
		entt::entity					m_player_entity;

		CameraSystem					m_camera_system;
		ControllerSystem				m_controller_system;
		RenderingSystem					m_rendering_system;
	};
}