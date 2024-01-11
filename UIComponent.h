#pragma once

#include <memory>
#include <unordered_map>

#include "UIComponentState.h"
#include "UIBehaviour.h"
#include "Vector2.h"

namespace hk::ui
{
	struct UIComponent
	{
		using BehaviourList = std::vector<std::unique_ptr<UIBehaviour>>;
		using StateList = std::unordered_map<std::string, UIComponentState>;

		UIComponent() = default;

		//unique_ptrs wreaking fucking havoc as per usual
		UIComponent(UIComponent&& rhs);
		UIComponent& operator=(UIComponent&& rhs);


		bool			is_visible = true;
		int				z_index = 0;
		Vector2f		position;
		Vector2i		dimensions;
		std::string		current_state;
		StateList		states;
		BehaviourList	behaviours;
	};

	SDL_Rect GetUIBounds(const UIComponent& ui_element);
	const UIComponentState& GetCurrentState(const UIComponent& ui_element);
	void SetText(UIComponent& ui_element, const std::string& new_text);
}