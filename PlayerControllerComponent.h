#pragma once

#include <entt/entt.hpp>
#include <memory>

namespace hk
{
	class ControllerInstance;

	struct PlayerControllerComponent
	{
		entt::entity						controlled_entity = entt::null;
		bool								is_enabled;
		std::string							id;
		std::unique_ptr<ControllerInstance> controller;
	};
}