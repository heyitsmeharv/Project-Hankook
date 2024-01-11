#include "ConstraintAttachment.h"

#include "CameraComponent.h"
#include "TransformComponent.h"

#include <entt/entt.hpp>

namespace hk
{
	ConstraintAttachment::ConstraintAttachment()
		: m_constraint()
	{
	}

	ConstraintAttachment::ConstraintAttachment(const SDL_FRect& constraint)
		: m_constraint()
	{
		SetConstraint(constraint);
	}

	void ConstraintAttachment::Update(entt::entity camera_entity, entt::registry& registry)
	{
		if (m_is_enabled)
		{
			CameraComponent& camera_component = registry.get<CameraComponent>(camera_entity);
			TransformComponent& camera_transform = registry.get<TransformComponent>(camera_entity);

			Vector2f position;
			position.x = std::clamp(camera_transform.position.x, m_constraint.x, m_constraint.w - camera_component.dimensions.x);
			position.y = std::clamp(camera_transform.position.y, m_constraint.y, m_constraint.h - camera_component.dimensions.y);

			if (position != camera_transform.position)
			{
				camera_transform.position = position;
			}
		}
	}

	void ConstraintAttachment::SetConstraint(const SDL_FRect& constraint)
	{
		m_constraint = constraint;
	}
}