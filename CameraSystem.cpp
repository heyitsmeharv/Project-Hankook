#include "CameraSystem.h"
#include <entt/entt.hpp>

#include "CameraComponent.h"
#include "TransformComponent.h"

namespace hk
{
	void CameraSystem::Update(entt::registry&)
	{
		if (m_cameras.empty())
		{
			return;
		}
	}

	void CameraSystem::PushNewCamera(entt::registry& registry, const CameraInitInfo& init_info)
	{
		entt::entity new_camera = registry.create();
		registry.emplace<TransformComponent>(new_camera, init_info.position);

		CameraComponent& camera_component = registry.emplace<CameraComponent>(new_camera);
		camera_component.id = init_info.id;
		camera_component.dimensions = init_info.dimensions;
		camera_component.zoom = init_info.zoom;

		m_cameras.push(new_camera);
	}

	void CameraSystem::PopCurrentCamera(entt::registry& registry)
	{
		registry.destroy(CurrentCamera());
		m_cameras.pop();
	}

	entt::entity CameraSystem::CurrentCamera() const
	{
		if (m_cameras.empty() == false)
		{
			return m_cameras.top();
		}

		return entt::null;
	}
}