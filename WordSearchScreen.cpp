#include "WordSearchScreen.h"

#include <entt/entt.hpp>

#include "CellButtonBehaviour.h"
#include "InputDeviceManager.h"
#include "ProcessLocationQueryModelCommand.h"

#include "CountdownModeComponent.h"
#include "GridComponent.h"
#include "TimedModeComponent.h"
#include "UIComponent.h"

#include "WordSearchModel.h"
#include "WordSearchModelAccess.h"
#include "WordFoundEvent.h"

namespace hk::ui
{
	WordSearchScreen::WordSearchScreen(entt::registry& registry)
		: UIScreen(registry)
		, m_grid_entity(entt::null)
		, m_mode_entity(entt::null)
		, m_game_mode(GameModes::NUM_OF_MODES)
		, m_timer_entity(entt::null)
		, m_cell_list()
		, m_word_list()
	{
	}

	WordSearchScreen::~WordSearchScreen()
	{
	}

	void WordSearchScreen::SetGameInfo(const entt::entity grid_entity, const entt::entity mode_entity, const GameModes game_mode)
	{
		m_grid_entity = grid_entity;
		m_mode_entity = mode_entity;
		m_game_mode = game_mode;
	}

	void WordSearchScreen::OnCreate()
	{
		const GridComponent& grid_component = m_registry.get<GridComponent>(m_grid_entity);
		const Vector2i cell_dimensions{ 32, 32 };
	
		//Create cells
		for (int y = 0; y < grid_component.height; ++y)
		{
			for (int x = 0; x < grid_component.width; ++x)
			{
				entt::entity cell = m_cell_list.emplace_back(m_registry.create());
				const char cell_char = grid_component.cell_list[grid_component.CoordToIndex({ x, y })];

				UIComponent& ui_button = m_registry.emplace<UIComponent>(cell);
				ui_button.position = { (float)x * cell_dimensions.x, (float)y * cell_dimensions.y };
				ui_button.dimensions = cell_dimensions;
				ui_button.current_state = "not_found";
				ui_button.behaviours.emplace_back(std::make_unique<ui::CellButtonBehaviour>());

				UIComponentState not_found_state;
				not_found_state.asset_ids.push_back("Images\\button_rect.png");
				not_found_state.colour_mod = SDL_Color{ 220, 220, 220, 255 };
				not_found_state.text = cell_char;
				not_found_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
				ui_button.states.emplace("not_found", not_found_state);

				UIComponentState hovered_not_found_state;
				hovered_not_found_state.asset_ids.push_back("Images\\button_rect.png");
				hovered_not_found_state.colour_mod = SDL_Color{ 255, 255, 255, 255 };
				hovered_not_found_state.text = cell_char;
				hovered_not_found_state.text_colour = SDL_Color{ 255, 32, 32, 255 };
				ui_button.states.emplace("hovered_not_found", hovered_not_found_state);

				UIComponentState hovered_found_state;
				hovered_found_state.asset_ids.push_back("Images\\button_rect.png");
				hovered_found_state.colour_mod = SDL_Color{ 255, 255, 255, 255 };
				hovered_found_state.text = cell_char;
				hovered_found_state.text_colour = SDL_Color{ 255, 32, 32, 255 };
				ui_button.states.emplace("hovered_found", hovered_found_state);

				UIComponentState found_state;
				found_state.asset_ids.push_back("Images\\button_rect.png");
				found_state.colour_mod = SDL_Color{ 180, 180, 0, 255 };
				found_state.text = cell_char;
				found_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
				ui_button.states.emplace("found", found_state);
			}
		}

		//Create list of words
		{
			Vector2f current_position{ (float)cell_dimensions.x * grid_component.width, 0.0f };
			for (const auto& word : grid_component.word_list)
			{
				auto [itr, success] = m_word_list.emplace(word, m_registry.create());

				UIComponent& word_component = m_registry.emplace<UIComponent>(itr->second);
				word_component.position = current_position;
				word_component.dimensions = { 150, 40 };
				word_component.current_state = "not_found";

				UIComponentState not_found_state;
				not_found_state.text = word;
				not_found_state.text_colour = SDL_Color{ 0, 0, 0, 255 };
				word_component.states.emplace("not_found", not_found_state);

				UIComponentState found_state;
				found_state.text = word;
				found_state.text_colour = SDL_Color{ 0, 200, 0, 255 };
				word_component.states.emplace("found", found_state);

				current_position.y += 40.0f;
			}
		}

		{
			//Create timer
			m_timer_entity = m_registry.create();
			UIComponent& timer_component = m_registry.emplace<UIComponent>(m_timer_entity);
			timer_component.position = { (float)cell_dimensions.x * grid_component.width, 750.0f };
			timer_component.dimensions = { 150, 40 };
			timer_component.current_state = "active";
			timer_component.is_visible = m_game_mode == GameModes::TIMED || m_game_mode == GameModes::COUNTDOWN;

			UIComponentState active_state;
			active_state.text_colour = SDL_Color{ 255, 255, 255, 255 };
			timer_component.states.emplace("active", active_state);
		}
	}

	void WordSearchScreen::OnDestroy()
	{
		m_registry.erase<UIComponent>(m_timer_entity);
		m_timer_entity = entt::null;

		for (const auto& [_, word_entity] : m_word_list)
		{
			m_registry.erase<UIComponent>(word_entity);
		}
		m_word_list.clear();

		for (const auto& cell_entity : m_cell_list)
		{
			m_registry.erase<UIComponent>(cell_entity);
		}
		m_cell_list.clear();

		m_grid_entity = entt::null;
		m_mode_entity = entt::null;
		m_game_mode = GameModes::NUM_OF_MODES;
	}

	void WordSearchScreen::OnEnter()
	{
		static_cast<hk::utils::Reporter<hk::WordFoundEvent>*>(m_registry.ctx().get<WordSearchModelAccess>().model_access)->AddListener(*this);
	}

	void WordSearchScreen::OnExit()
	{
		static_cast<hk::utils::Reporter<hk::WordFoundEvent>*>(m_registry.ctx().get<WordSearchModelAccess>().model_access)->RemoveListener(*this);
	}

	void WordSearchScreen::HandleInput(const InputDeviceManager& input_manager)
	{
		const auto& drag_event = input_manager.GetDefaultKeyboardMouse().GetDragEvent();
		if (drag_event.has_value())
		{
			const Vector2i cell_dims{ 32, 32 };
			const Vector2i start_cell = drag_event->start_pos / cell_dims;
			const Vector2i end_cell = drag_event->end_pos / cell_dims;
			const Vector2i delta = end_cell - start_cell;

			//If the delta is neither 0 or matching then we've got a duff query! (i.e. not properly diagonal, vertical or horizontal)
			if (delta.IsZeroed() == false && (delta.x == 0 || delta.y == 0 || std::abs(delta.x) == std::abs(delta.y)))
			{
				//If one of the cells is out of bounds then ignore the query
				const GridComponent& grid_component = m_registry.get<GridComponent>(m_grid_entity);
				if (start_cell.x >= 0 && start_cell.x < grid_component.width && end_cell.x >= 0 && end_cell.x < grid_component.width &&
					start_cell.y >= 0 && start_cell.y < grid_component.height && end_cell.y >= 0 && end_cell.y < grid_component.height)
				{
					//Now we know that we have a valid query, lets create a list of all cells in the query
					const Vector2f direction_norm = delta.AsNormalised();
					const Vector2i direction{ (int)std::round(direction_norm.x), (int)std::round(direction_norm.y) };

					std::vector<Vector2i> cell_list;
					for (Vector2i current_cell = start_cell; current_cell != end_cell; current_cell += direction)
					{
						cell_list.push_back(current_cell);
					}
					cell_list.push_back(end_cell);

					//Finally send the query off to see if the selected cells are a word!
					auto query_cmd = std::make_unique<ProcessLocationQueryModelCommand>(cell_list, m_grid_entity);
					m_registry.ctx().get<WordSearchModelAccess>().model_access->QueueModelCommand(std::move(query_cmd));
				}
			}
		}
	}

	void WordSearchScreen::Update(const double /*delta_time*/)
	{
		switch (m_game_mode)
		{
			case GameModes::TIMED:
			{
				TimedModeComponent* mode_component = m_registry.try_get<TimedModeComponent>(m_mode_entity);
				UIComponent* timer_component = m_registry.try_get<UIComponent>(m_timer_entity);
				if (mode_component && timer_component)
				{
					SetText(*timer_component, std::to_string((int)mode_component->current_time));
				}
				break;
			}
			case GameModes::COUNTDOWN:
			{
				CountdownModeComponent* mode_component = m_registry.try_get<CountdownModeComponent>(m_mode_entity);
				UIComponent* timer_component = m_registry.try_get<UIComponent>(m_timer_entity);
				if (mode_component && timer_component)
				{
					SetText(*timer_component, std::to_string((int)mode_component->time_left));
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void WordSearchScreen::Notify(const WordFoundEvent& found_event)
	{
		const GridComponent& grid_component = m_registry.get<GridComponent>(m_grid_entity);

		//Set all cells to found state
		for (const auto& cell_coord : found_event.cell_list)
		{
			entt::entity cell_entity = m_cell_list[grid_component.CoordToIndex(cell_coord)];

			UIComponent* ui_component = m_registry.try_get<UIComponent>(cell_entity);
			if (ui_component)
			{
				ui_component->current_state = "found";
			}
		}

		//Set word in word list to found
		const auto& itr = m_word_list.find(found_event.found_word);
		if (itr != m_word_list.end())
		{
			UIComponent* word_component = m_registry.try_get<UIComponent>(itr->second);
			if (word_component)
			{
				word_component->current_state = "found";
			}
		}
	}
}