#include "CameraSystem.h"
#include <entt/entt.hpp>

#include "CameraComponent.h"
#include "CameraAttachment.h"
#include "TransformComponent.h"

namespace hk
{
	void CameraSystem::Update(entt::registry& registry)
	{
		if (m_cameras.empty())
		{
			return;
		}

		entt::entity current_camera_entity = CurrentCamera();
		CameraComponent* current_camera = registry.try_get<CameraComponent>(current_camera_entity);
		if (current_camera)
		{
			for (auto& attachment : current_camera->attachments)
			{
				if (attachment && attachment->IsEnabled())
				{
					attachment->Update(current_camera_entity, registry);
				}
			}
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

	bool CameraSystem::AddAttachment(entt::registry& registry, entt::entity camera_entity, std::unique_ptr<CameraAttachment>&& attachment)
	{
		CameraComponent* camera_component = registry.try_get<CameraComponent>(camera_entity);
		if (camera_component)
		{
			camera_component->attachments.push_back(std::move(attachment));
			return true;
		}

		return false;
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