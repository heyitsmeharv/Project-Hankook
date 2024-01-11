#pragma once

#include <entt/fwd.hpp>
#include "GameModes.h"

#include "ListenerReporter.h"

namespace hk
{
	struct WordFoundEvent;

	class GameModeSystem : public hk::utils::Listener<WordFoundEvent>
	{
	public:
		 GameModeSystem(entt::registry& registry);
		~GameModeSystem();

		void		Initialise		();
		void		Close			();
		void		Update			(const double delta_time);

		void		SetCurrentMode	(entt::entity grid_component, GameModes game_mode, entt::entity current_mode_entity);
		bool		IsGameOver		() const;

		void		Notify			(const WordFoundEvent& found_event) override;

		double		GetCurrentTimeOnTimer	() const;
		GameModes	GetCurrentMode			() const;

	private:
		entt::registry& m_registry;
		bool			m_is_game_over;
		GameModes		m_current_mode;
		entt::entity	m_current_mode_entity;
		entt::entity	m_grid_entity;
	};
}