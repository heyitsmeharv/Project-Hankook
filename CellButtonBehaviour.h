#pragma once

#include "UIBehaviour.h"

namespace hk::ui
{
	class CellButtonBehaviour final : public UIBehaviour
	{
	public:
		void OnHoverOn	(UIComponent& owner) override;
		void OnHoverOff	(UIComponent& owner) override;
	};
}