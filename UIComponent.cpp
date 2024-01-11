#include "UIComponent.h"

namespace hk::ui
{
	UIComponent::UIComponent(UIComponent&& rhs)
	{
		is_visible = rhs.is_visible;
		z_index = rhs.z_index;
		position = rhs.position;
		dimensions = rhs.dimensions;
		current_state = std::move(rhs.current_state);
		states = std::move(rhs.states);
		behaviours = std::move(rhs.behaviours);

		rhs.is_visible = false;
		rhs.z_index = 0;
		rhs.position = {};
		rhs.dimensions = {};
	}

	UIComponent& UIComponent::operator=(UIComponent&& rhs)
	{
		is_visible = rhs.is_visible;
		z_index = rhs.z_index;
		position = rhs.position;
		dimensions = rhs.dimensions;
		current_state = std::move(rhs.current_state);
		states = std::move(rhs.states);
		behaviours = std::move(rhs.behaviours);

		rhs.is_visible = false;
		rhs.z_index = 0;
		rhs.position = {};
		rhs.dimensions = {};

		return *this;
	}

	SDL_Rect GetUIBounds(const UIComponent& ui_element)
	{
		return { (int)ui_element.position.x, (int)ui_element.position.y, ui_element.dimensions.x, ui_element.dimensions.y };
	}

	const UIComponentState& GetCurrentState(const UIComponent& ui_element)
	{
		const auto& itr = ui_element.states.find(ui_element.current_state);
		if (itr != ui_element.states.end())
		{
			return itr->second;
		}

		return ui_element.states.begin()->second;
	}

	void SetText(UIComponent& ui_element, const std::string& new_text)
	{
		for (auto& [_, state] : ui_element.states)
		{
			state.SetText(new_text);
		}
	}
}