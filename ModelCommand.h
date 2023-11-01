#pragma once

#include <entt/fwd.hpp>

namespace hk
{
	class ModelCommand
	{
	public:
		virtual ~ModelCommand() {}
		virtual void Execute(entt::registry& registry) = 0;
	};
}