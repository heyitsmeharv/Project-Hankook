#include "Camera.h"
#include "CameraAttachment.h"

#include <algorithm>

namespace hk
{
	Camera::Camera(const CameraInitInfo& init)
		: Transformable(init.position)
		, m_dimensions(init.dimensions)
		, m_constraints(init.contraints)
	{
		if (m_constraints.has_value())
		{
			m_constraints->w -= m_dimensions.x;
			m_constraints->h -= m_dimensions.y;
		}
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
		for (auto& attachment : m_attachments)
		{
			attachment->Update(*this);
		}
	}

	void Camera::ChangeDimensions(const Vector2i& delta)
	{
		m_dimensions += delta;
	}

	void Camera::SetDimensions(const Vector2i& new_dims)
	{
		m_dimensions = new_dims;
	}

	const Vector2i& Camera::GetDimensions() const
	{
		return m_dimensions;
	}

	SDL_Rect Camera::GetCameraRect() const
	{
		return { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_dimensions.x, m_dimensions.y };
	}

	void Camera::SetPosition(float new_x_pos, float new_y_pos)
	{
		SetPosition({ new_x_pos, new_y_pos });
	}

	void Camera::SetPosition(const Vector2f& new_pos)
	{
		m_position = new_pos;
		ClampToConstraint();
	}

	void Camera::MovePosition(float x_delta, float y_delta)
	{
		MovePosition({ x_delta, y_delta });
	}

	void Camera::MovePosition(const Vector2f& delta)
	{
		m_position += delta;
		ClampToConstraint();
	}

	void Camera::ClampToConstraint()
	{
		if (m_constraints.has_value())
		{
			m_position.x = std::clamp(m_position.x, m_constraints->x, m_constraints->w);
			m_position.y = std::clamp(m_position.y, m_constraints->y, m_constraints->h);
		}
	}

	void Camera::AddAttachment(std::unique_ptr<CameraAttachment>&& attachment)
	{
		m_attachments.push_back(std::move(attachment));
	}
}