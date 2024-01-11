#include "GameOverScreen.h"

#include "GridComponent.h"
#include "UIComponent.h"

#include "CommandButtonBehaviour.h"
#include "WordSearchModel.h"
#include "WordSearchModelAccess.h"

#include <Windows.h>

namespace hk::ui
{
	GameOverScreen::GameOverScreen(entt::registry& registry, const GameOverScreenInitInfo& init_info)
		: UIScreen(registry)
		, m_init_info(init_info)
		, m_title(entt::null)
	{
	}

	GameOverScreen::~GameOverScreen()
	{
	}

	void GameOverScreen::OnCreate()
	{
		m_title = m_registry.create();

		UIComponent& title_component = m_registry.emplace<UIComponent>(m_title);
		title_component.position = { 400.0f, 20.0f };
		title_component.dimensions = Vector2i{ 500, 64 };
		title_component.current_state = "default";

		UIComponentState default_state;
		default_state.text = "GAME OVER";
		default_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
		title_component.states.emplace("default", default_state);

		Vector2f current_position{ 400.0f, 100.0f };
		GridComponent* grid_component = m_registry.try_get<GridComponent>(m_init_info.grid_entity);
		if (grid_component)
		{
			for (const auto& [word, word_info] : grid_component->word_infos)
			{
				entt::entity entry_entity = m_word_list.emplace_back(m_registry.create());

				UIComponent& entry_component = m_registry.emplace<UIComponent>(entry_entity);
				entry_component.position = current_position;
				entry_component.dimensions = Vector2i{ 500, 64 };
				entry_component.current_state = word_info.is_found ? "found" : "not_found";

				UIComponentState found_state;
				found_state.text = word;
				found_state.text_colour = SDL_Color{ 0, 255, 0, 255 };
				entry_component.states.emplace("found", found_state);

				UIComponentState not_found_state;
				not_found_state.text = word;
				not_found_state.text_colour = SDL_Color{ 255, 0, 0, 255 };
				entry_component.states.emplace("not_found", not_found_state);

				current_position.y += 64.0f;
			}
		}

		m_restart_button= m_word_list.emplace_back(m_registry.create());

		UIComponent& restart_button = m_registry.emplace<UIComponent>(m_restart_button);
		restart_button.position = { 800.0f, 100.0f };
		restart_button.dimensions = { 300, 64 };
		restart_button.current_state = "active";
		restart_button.behaviours.emplace_back(std::make_unique<CommandButtonBehaviour>([&]() 
		{
			
		}));

		UIComponentState active_state;
		active_state.asset_ids.push_back("Images\\button_rect.png");
		active_state.colour_mod = SDL_Color{ 220, 220, 220, 255 };
		active_state.text = "RESTART";
		active_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
		restart_button.states.emplace("active", active_state);

		UIComponentState hovered_state;
		hovered_state.asset_ids.push_back("Images\\button_rect.png");
		hovered_state.colour_mod = SDL_Color{ 255, 255, 255, 255 };
		hovered_state.text = "RESTART";
		hovered_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
		restart_button.states.emplace("hovered", hovered_state);

		UIComponentState selected_state;
		selected_state.asset_ids.push_back("Images\\button_rect.png");
		selected_state.colour_mod = SDL_Color{ 240, 240, 240, 255 };
		selected_state.text = "RESTART";
		selected_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
		restart_button.states.emplace("selected", selected_state);
	}

	void GameOverScreen::OnDestroy()
	{
		for (const auto& word_entity : m_word_list)
		{
			m_registry.erase<UIComponent>(word_entity);
		}
		m_word_list.clear();

		m_registry.erase<UIComponent>(m_title);
	}

	void GameOverScreen::OnEnter()
	{
	}

	void GameOverScreen::OnExit()
	{
	}

	void GameOverScreen::HandleInput(const InputDeviceManager&)
	{
	}

	void GameOverScreen::Update(const double delta_time)
	{
		
	}
}