#pragma once

#include <entt/fwd.hpp>
#include <stack>
#include <string>

#include "Vector2.h"

namespace hk
{
	struct CameraInitInfo
	{
		std::string	id;
		Vector2f	position;
		Vector2i	dimensions;
		float		zoom;
	};

	class CameraSystem
	{
	public:
		void			Update			(entt::registry& registry);

		void			PushNewCamera	(entt::registry& registry, const CameraInitInfo& init_info);
		void			PopCurrentCamera(entt::registry& registry);

		entt::entity	CurrentCamera	() const;

	private:
		std::stack<entt::entity> m_cameras;
	};
}