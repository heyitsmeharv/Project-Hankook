#pragma once

namespace hk::ui
{
	struct UIComponent;

	class UIBehaviour
	{
	public:
		virtual ~UIBehaviour() {}

		virtual void OnHoverOn		(UIComponent&) {}
		virtual void OnHoverOff		(UIComponent&) {}
		virtual void OnLClickDown	(UIComponent&) {}
		virtual void OnLClickUp		(UIComponent&) {}
		virtual void OnRClickDown	(UIComponent&) {}
		virtual void OnRClickUp		(UIComponent&) {}
	};
}