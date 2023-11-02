#pragma once

#include <entt/entt.hpp>
#include <memory>

namespace hk
{
	class ControllerInstance;

	struct PlayerControllerComponent
	{
		std::string							id;
		entt::entity						controlled_entity = entt::null;
		bool								is_enabled = false;
		std::unique_ptr<ControllerInstance> controller = nullptr;
	};
}