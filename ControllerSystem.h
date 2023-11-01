#pragma once

#include <entt/fwd.hpp>
#include <vector>

namespace hk
{
	class ControllerSystem
	{
	public:
		void Update(entt::registry& registry) const;
	};
}