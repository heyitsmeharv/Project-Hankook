#pragma once

#include "CameraAttachment.h"
#include "Vector2.h"

namespace hk
{
	class LockOnAttachment final : public CameraAttachment
	{
	public:
		LockOnAttachment();
		LockOnAttachment(entt::entity target_entity, const Vector2f& offset);

		void Update(entt::entity camera_entity, entt::registry& registry) override;

		void AttachToTarget(entt::entity target_entity, const Vector2f& offset);

		void			SetOffset	(const Vector2f& new_offset);
		void			MoveOffset	(const Vector2f& delta);
		const Vector2f& GetOffset	() const;

	private:
		entt::entity	m_target;
		Vector2f		m_offset;
	};
}