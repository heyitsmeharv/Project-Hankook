#pragma once

#include <entt/fwd.hpp>

namespace hk
{
	class InputDeviceManager;
}

namespace hk::ui
{
	class UIScreen
	{
	public:
		UIScreen(entt::registry& registry) : m_registry(registry) {}
		virtual ~UIScreen() {}

		virtual void OnCreate		() = 0;
		virtual void OnDestroy		() = 0;

		virtual void OnEnter		() = 0;
		virtual void OnExit			() = 0;
		virtual void HandleInput	(const InputDeviceManager&) = 0;
		virtual void Update			(double delta_time) = 0;

	protected:
		entt::registry& m_registry;
	};
}