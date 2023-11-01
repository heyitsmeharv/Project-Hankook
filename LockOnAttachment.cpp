#include "LockOnAttachment.h"
#include "TransformComponent.h"

#include <entt/entt.hpp>

namespace hk
{
	LockOnAttachment::LockOnAttachment()
		: m_target(entt::null)
		, m_offset()
	{
	}

	LockOnAttachment::LockOnAttachment(entt::entity target_entity, const Vector2f& offset)
		: m_target(target_entity)
		, m_offset(offset)
	{
	}

	void LockOnAttachment::Update(entt::entity camera_entity, entt::registry& registry)
	{
		if (m_is_enabled && m_target != entt::null)
		{
			TransformComponent& camera_transform = registry.get<TransformComponent>(camera_entity);
			TransformComponent& target_transform = registry.get<TransformComponent>(m_target);
			
			camera_transform.position = target_transform.position - m_offset;
		}
	}

	void LockOnAttachment::SetOffset(const Vector2f& new_offset)
	{
		m_offset = new_offset;
	}

	void LockOnAttachment::MoveOffset(const Vector2f& delta)
	{
		m_offset += delta;
	}

	void LockOnAttachment::AttachToTarget(entt::entity target_entity, const Vector2f& offset)
	{
		m_target = target_entity;
		m_offset = offset;
	}

	const Vector2f& LockOnAttachment::GetOffset() const
	{
		return m_offset;
	}
}