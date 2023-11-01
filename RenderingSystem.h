#pragma once

#include <entt/fwd.hpp>

namespace hk
{
	class RenderingSystem
	{
	public:
		void Update(entt::registry& registry, entt::entity current_camera) const;
	};
}