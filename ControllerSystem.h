#pragma once

#include <entt/fwd.hpp>
#include <vector>

namespace hk
{
	class GameModel;

	class ControllerSystem
	{
	public:
		void Update(entt::registry& registry, GameModel& model) const;
	};
}