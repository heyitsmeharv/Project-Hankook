#pragma once

#include <memory>
#include <entt/entt.hpp>

#include "CommandQueue.h"
#include "BaseModel.h"
#include "ModelCommand.h"

#include "CameraSystem.h"
#include "ControllerSystem.h"
#include "GameModeSystem.h"
#include "InteractionSystem.h"
#include "RenderingSystem.h"
#include "UISystem.h"

#include "Timer.h"

#include "ListenerReporter.h"

namespace hk
{
	struct WordFoundEvent;

	class WordSearchModel final : public BaseModel
								, public utils::Reporter<WordFoundEvent>
	{
	public:
		WordSearchModel(Engine& engine);
		~WordSearchModel();

		void Initialise		() override;
		void Destroy		() override;
		void Update			(const double delta_time) override;

		void QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command);

		const entt::registry& GetRegistry() const;

		void OnWordFound(const std::string& word, std::vector<Vector2i>&& cell_list);

	private:
		bool LoadPlayerController	();
		void ProcessModelCommands	();
		void HandleGameOver			();

	private:
		CommandQueue<ModelCommand>		m_model_command_queue;
		entt::registry					m_registry;
		CameraSystem					m_camera_system;
		GameModeSystem					m_game_mode_system;
		RenderingSystem					m_rendering_system;
		UISystem						m_ui_system;

		entt::entity					m_grid_entity;
	};
}