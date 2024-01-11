#pragma once

#include "UIScreen.h"

#include <entt/entt.hpp>
#include <vector>

#include "GameModes.h"

namespace hk::ui
{
	struct GameOverScreenInitInfo
	{
		entt::entity	grid_entity = entt::null;
		GameModes		game_mode = GameModes::NUM_OF_MODES;
		double			finish_time = 0.0;
	};

	class GameOverScreen final : public UIScreen
	{
	public:
		 GameOverScreen(entt::registry& registry, const GameOverScreenInitInfo& init_info);
		~GameOverScreen();

		void OnCreate		() override;
		void OnDestroy		() override;

		void OnEnter		() override;
		void OnExit			() override;
		void HandleInput	(const InputDeviceManager&) override;
		void Update			(double delta_time) override;

	private:
		GameOverScreenInitInfo		m_init_info;

		entt::entity				m_title;
		std::vector<entt::entity>	m_word_list;
		entt::entity				m_restart_button;
	};
}