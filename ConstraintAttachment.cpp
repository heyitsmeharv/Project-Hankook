#include "ConstraintAttachment.h"
#include "Camera.h"

#include <algorithm>

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

	void ConstraintAttachment::Update(Camera& camera)
	{
		if (m_is_enabled)
		{
			Vector2f position = camera.GetPosition();

			position.x = std::clamp(position.x, m_constraint.x, m_constraint.w - camera.GetCameraRect().w);
			position.y = std::clamp(position.y, m_constraint.y, m_constraint.h - camera.GetCameraRect().h);

			if (position != camera.GetPosition())
			{
				camera.SetPosition(position);
			}
		}
	}

	void ConstraintAttachment::SetConstraint(const SDL_FRect& constraint)
	{
		m_constraint = constraint;
	}
}