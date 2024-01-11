#pragma once

#include <entt/fwd.hpp>
#include <memory>

namespace hk
{
	class InputDeviceManager;

	namespace ui
	{
		struct	UIComponent;
		class	UIScreen;
	}

	class UISystem
	{
	public:
		 UISystem(entt::registry& registry);

		void Update		(double delta_time);
		void HandleInput(const InputDeviceManager& input_manager);

		void ChangeScreen(std::unique_ptr<ui::UIScreen>&& new_screen);

	private:
		entt::registry&					m_registry;
		std::unique_ptr<ui::UIScreen>	m_current_screen;
		ui::UIComponent*				m_hovered_element;
	};
}