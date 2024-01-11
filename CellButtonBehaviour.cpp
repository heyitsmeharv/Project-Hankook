#include "CellButtonBehaviour.h"
#include "UIComponent.h"

namespace hk::ui
{
	void CellButtonBehaviour::OnHoverOn(UIComponent& owner)
	{
		if (owner.current_state == "not_found")
		{
			owner.current_state = "hovered_not_found";
		}
		else if (owner.current_state == "found")
		{
			owner.current_state = "hovered_found";
		}
	}

	void CellButtonBehaviour::OnHoverOff(UIComponent& owner)
	{
		if (owner.current_state == "hovered_not_found")
		{
			owner.current_state = "not_found";
		}
		else if (owner.current_state == "hovered_found")
		{
			owner.current_state = "found";
		}
	}
}