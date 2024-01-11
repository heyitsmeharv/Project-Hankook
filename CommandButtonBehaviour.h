#pragma once

#include "UIBehaviour.h"

namespace hk::ui
{
	class CommandButtonBehaviour final : public UIBehaviour
	{
	public:
		using Callable = void(*)();

		CommandButtonBehaviour(Callable click_func);

		void OnHoverOn		(UIComponent&) override;
		void OnHoverOff		(UIComponent&) override;
		void OnLClickDown	(UIComponent&) override;
		void OnLClickUp		(UIComponent&) override;

	private:
		Callable m_click_func;
	};
}