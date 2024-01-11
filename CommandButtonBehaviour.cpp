#include "CommandButtonBehaviour.h"

#include "UIComponent.h"

namespace hk::ui
{
	CommandButtonBehaviour::CommandButtonBehaviour(Callable click_func)
		: m_click_func(click_func)
	{
	}

	void CommandButtonBehaviour::OnHoverOn(UIComponent& ui_element)
	{
		ui_element.current_state = "hovered";
	}

	void CommandButtonBehaviour::OnHoverOff(UIComponent& ui_element)
	{
		ui_element.current_state = "active";
	}

	void CommandButtonBehaviour::OnLClickDown(UIComponent& ui_element)
	{
		ui_element.current_state = "pressed";
		m_click_func();
	}

	void CommandButtonBehaviour::OnLClickUp(UIComponent& ui_element)
	{
		ui_element.current_state = "hovered";
	}
}