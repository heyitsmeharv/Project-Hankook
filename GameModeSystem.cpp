#include "GameModeSystem.h"

#include <entt/entt.hpp>

#include "CountdownModeComponent.h"
#include "NormalModeComponent.h"
#include "TimedModeComponent.h"
#include "GridComponent.h"

#include "WordSearchModel.h"
#include "WordSearchModelAccess.h"

namespace hk
{
	GameModeSystem::GameModeSystem(entt::registry& registry)
		: m_registry(registry)
		, m_is_game_over(false)
		, m_current_mode(GameModes::NUM_OF_MODES)
		, m_current_mode_entity(entt::null)
		, m_grid_entity(entt::null)
	{
	}

	GameModeSystem::~GameModeSystem()
	{
		Close();
	}

	void GameModeSystem::Initialise()
	{
		static_cast<hk::utils::Reporter<hk::WordFoundEvent>*>(m_registry.ctx().get<WordSearchModelAccess>().model_access)->AddListener(*this);
	}

	void GameModeSystem::Close()
	{
		static_cast<hk::utils::Reporter<hk::WordFoundEvent>*>(m_registry.ctx().get<WordSearchModelAccess>().model_access)->RemoveListener(*this);
	}

	void GameModeSystem::Update(const double delta_time)
	{
		if (m_is_game_over)
		{
			return;
		}

		switch (m_current_mode)
		{
			case GameModes::NORMAL:
			{
				NormalModeComponent* mode_component = m_registry.try_get<NormalModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					mode_component->current_time += delta_time;
				}
				break;
			}
			case GameModes::TIMED:
			{
				TimedModeComponent* mode_component = m_registry.try_get<TimedModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					mode_component->current_time += delta_time;
				}
				break;
			}
			case GameModes::COUNTDOWN:
			{
				CountdownModeComponent* mode_component = m_registry.try_get<CountdownModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					mode_component->time_left -= delta_time;
					if (mode_component->time_left <= 0.0)
					{
						m_is_game_over = true;
					}
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void GameModeSystem::SetCurrentMode(const entt::entity grid_entity, GameModes game_mode, entt::entity current_mode_entity)
	{
		m_grid_entity = grid_entity;
		m_current_mode = game_mode;
		m_current_mode_entity = current_mode_entity;
	}

	void GameModeSystem::Notify(const WordFoundEvent& /*found_event*/)
	{
		const GridComponent* grid_component = m_registry.try_get<GridComponent>(m_grid_entity);
		if (grid_component)
		{
			m_is_game_over = grid_component->IsComplete();
		}
	}

	bool GameModeSystem::IsGameOver() const
	{
		return m_is_game_over;
	}

	double GameModeSystem::GetCurrentTimeOnTimer() const
	{
		switch (m_current_mode)
		{
			case GameModes::NORMAL:
			{
				NormalModeComponent* mode_component = m_registry.try_get<NormalModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					return mode_component->current_time;
				}
			}
			case GameModes::TIMED:
			{
				TimedModeComponent* mode_component = m_registry.try_get<TimedModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					return mode_component->current_time;
				}
			}
			case GameModes::COUNTDOWN:
			{
				CountdownModeComponent* mode_component = m_registry.try_get<CountdownModeComponent>(m_current_mode_entity);
				if (mode_component)
				{
					return mode_component->time_limit_in_s - mode_component->time_left;
				}
			}
			default:
			{
				return 0.0;
			}
		}

		return 0.0;
	}

	GameModes GameModeSystem::GetCurrentMode() const
	{
		return m_current_mode;
	}
}