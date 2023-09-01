#include "Camera.h"
#include "CameraAttachment.h"

namespace hk
{
	Camera::Camera()
		: Transformable()
		, m_dimensions()
	{
	}

	Camera::Camera(const CameraInitInfo& init)
		: Transformable(init.position)
		, m_dimensions(init.dimensions)
	{
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
	}

	void Camera::MovePosition(float x_delta, float y_delta)
	{
		MovePosition({ x_delta, y_delta });
	}

	void Camera::MovePosition(const Vector2f& delta)
	{
		m_position += delta;
	}

	void Camera::AddAttachment(std::unique_ptr<CameraAttachment>&& attachment)
	{
		m_attachments.push_back(std::move(attachment));
	}
}