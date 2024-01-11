#include "UISystem.h"
#include "UIScreen.h"

#include "GridComponent.h"
#include "UIComponent.h"

#include <entt/entt.hpp>

#include "InputDeviceManager.h"
#include "KeyboardMouseDevice.h"

namespace hk
{
	UISystem::UISystem(entt::registry& registry)
		: m_registry(registry)
		, m_current_screen(nullptr)
		, m_hovered_element(nullptr)
	{
	}

	void UISystem::Update(const double delta_time)
	{
		if (m_current_screen)
		{
			SDL_Point mouse_pos{ 0, 0 };
			SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
			ui::UIComponent* cached_hovered_element = m_hovered_element;

			//Are we still hovered over the hovered element
			if (m_hovered_element)
			{
				const SDL_Rect ui_bounds = ui::GetUIBounds(*m_hovered_element);
				if (SDL_PointInRect(&mouse_pos, &ui_bounds) == false)
				{
					for (const auto& behaviour : m_hovered_element->behaviours)
					{
						if (behaviour)
						{
							behaviour->OnHoverOff(*m_hovered_element);
						}
					}

					m_hovered_element = nullptr;
				}
			}

			//Check to see if we're hovering over any elements
			auto ui_view = m_registry.view<ui::UIComponent>();
			ui_view.each([&](ui::UIComponent& ui_element) 
			{
				if(m_hovered_element == nullptr || ui_element.z_index > m_hovered_element->z_index)
				{
					const SDL_Rect ui_bounds = ui::GetUIBounds(ui_element);
					if (SDL_PointInRect(&mouse_pos, &ui_bounds))
					{
						//We don't break here as we could find another component with an even higher z index
						m_hovered_element = &ui_element;
					}
				}
			});

			//If we are hovering over an element but we've changed then call the OnHover
			if (m_hovered_element && m_hovered_element != cached_hovered_element)
			{
				for (const auto& behaviour : m_hovered_element->behaviours)
				{
					if (behaviour)
					{
						behaviour->OnHoverOn(*m_hovered_element);
					}
				}
			}

			m_current_screen->Update(delta_time);
		}
	}

	void UISystem::HandleInput(const InputDeviceManager& input_manager)
	{
		if (m_hovered_element && input_manager.GetDefaultKeyboardMouse().IsMouseButtonPressed(SDL_BUTTON_LEFT))
		{
			for (const auto& behaviour : m_hovered_element->behaviours)
			{
				if (behaviour)
				{
					behaviour->OnLClickDown(*m_hovered_element);
				}
			}
		}

		if (m_current_screen)
		{
			m_current_screen->HandleInput(input_manager);
		}
	}

	void UISystem::ChangeScreen(std::unique_ptr<ui::UIScreen>&& new_screen)
	{
		if (m_current_screen)
		{
			m_current_screen->OnExit();
			m_current_screen->OnDestroy();
		}

		m_current_screen = std::move(new_screen);
		m_current_screen->OnCreate();
		m_current_screen->OnEnter();
	}
}