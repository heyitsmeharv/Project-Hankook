#pragma once

#include "CameraAttachment.h"
#include "Vector2.h"

namespace hk
{
	class Transformable;

	class LockOnAttachment final : public CameraAttachment
	{
	public:
		LockOnAttachment();
		LockOnAttachment(const Transformable& target, const Vector2f& offset);

		void Update(Camera& camera) override;

		void AttachToTarget(const Transformable& target, const Vector2f& offset);

		void			SetOffset	(const Vector2f& new_offset);
		void			MoveOffset	(const Vector2f& delta);
		const Vector2f& GetOffset	() const;

	private:
		const Transformable*	m_target;
		Vector2f				m_offset;
	};
}