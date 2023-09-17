#pragma once

#include <memory>

#include "CommandQueue.h"
#include "IModel.h"
#include "ModelCommand.h"
#include "PlayerController.h"
#include "Tilemap.h"

namespace hk
{
	class CameraManager;
	class Engine;
	class GameObject;

	class GameModel final : public IModel
	{
	public:
		 GameModel(Engine& engine);
		~GameModel();

		void Initialise	() override;
		void Destroy	() override;
		void Update		(const double delta_time) override;
		void Draw		() const override;

		bool LoadPlayerController();

		void QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command);

	private:
		void ProcessModelCommands();

	private:
		Engine&							m_engine;

		PlayerController				m_player_controller;
		Tilemap							m_tilemap;
		std::unique_ptr<hk::GameObject> m_root_object;
		CommandQueue<ModelCommand>		m_model_command_queue;
	};
}