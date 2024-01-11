#pragma once

#include "UIScreen.h"
#include "ListenerReporter.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "GameModes.h"

namespace hk
{
	struct WordFoundEvent;
}

namespace hk::ui
{
	class WordSearchScreen final : public UIScreen
								 , public hk::utils::Listener<hk::WordFoundEvent>
	{
	public:
		 WordSearchScreen(entt::registry& registry);
		~WordSearchScreen();

		void SetGameInfo	(entt::entity grid_entity, entt::entity mode_entity, GameModes game_mode);

		void OnCreate		() override;
		void OnDestroy		() override;

		void OnEnter		() override;
		void OnExit			() override;
		void HandleInput	(const InputDeviceManager& input_manager) override;
		void Update			(double delta_time) override;

		void Notify			(const WordFoundEvent& found_event) override;

	private:
		entt::entity m_grid_entity;
		entt::entity m_mode_entity;
		GameModes	 m_game_mode;

		entt::entity									m_timer_entity;
		std::vector<entt::entity>						m_cell_list;
		std::unordered_map<std::string, entt::entity>	m_word_list;
	};
}