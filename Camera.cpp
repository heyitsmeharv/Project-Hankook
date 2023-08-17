#include "Camera.h"

namespace hk
{
	Camera::Camera(const CameraInitInfo& init)
		: Transformable(init.position)
		, m_dimensions(init.dimensions)
	{
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
}