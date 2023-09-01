#include "LockOnAttachment.h"
#include "Camera.h"

namespace hk
{
	LockOnAttachment::LockOnAttachment()
		: m_target(nullptr)
		, m_offset()
	{
	}

	LockOnAttachment::LockOnAttachment(const Transformable& target, const Vector2f& offset)
		: m_target(&target)
		, m_offset(offset)
	{
	}

	void LockOnAttachment::Update(Camera& camera)
	{
		if (m_is_enabled && m_target)
		{
			camera.SetPosition(m_target->GetPosition() - m_offset);
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

	const Vector2f& LockOnAttachment::GetOffset() const
	{
		return m_offset;
	}
}