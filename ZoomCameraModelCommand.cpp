#include "ZoomCameraModelCommand.h"

#include <entt/entt.hpp>
#include "CameraComponent.h"

namespace hk
{
	ZoomCameraModelCommand::ZoomCameraModelCommand(entt::entity entity, const float delta)
		: m_entity(entity)
		, m_delta(delta)
	{
	}

	void ZoomCameraModelCommand::Execute(entt::registry& registry)
	{
		CameraComponent& camera = registry.get<CameraComponent>(m_entity);
		camera.zoom += m_delta;
	}
}