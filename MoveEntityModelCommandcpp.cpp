#include "MoveEntityModelCommand.h"

#include <entt/entt.hpp>
#include "TransformComponent.h"

namespace hk
{
	MoveEntityModelCommand::MoveEntityModelCommand(entt::entity entity, const Vector2f delta)
		: m_entity(entity)
		, m_delta(delta)
	{
	}

	void MoveEntityModelCommand::Execute(entt::registry& registry)
	{
		TransformComponent& transform = registry.get<TransformComponent>(m_entity);
		transform.position += m_delta;
	}
}