#include "Drawable.h"

namespace hk
{
	Drawable::Drawable()
		: m_rotation_in_deg(0)
		, m_scale()
		, m_flip(SDL_RendererFlip::SDL_FLIP_NONE)
	{
	}

	Drawable::~Drawable()
	{
	}

	void Drawable::SetDimensions(const Vector2i& new_dimensions)
	{
		m_dimensions = new_dimensions;
	}

	void Drawable::SetWidth(const int width)
	{
		m_dimensions.x = width;
	}

	void Drawable::SetHeight(const int height)
	{
		m_dimensions.y = height;
	}

	void Drawable::SetRotation(int new_rot_in_deg)
	{
		m_rotation_in_deg = new_rot_in_deg;
	}

	void Drawable::AddRotation(int delta_rot_in_deg)
	{
		m_rotation_in_deg += delta_rot_in_deg;
	}

	void Drawable::SetScale(float new_x_scale, float new_y_scale)
	{
		m_scale.x = new_x_scale;
		m_scale.y = new_y_scale;
	}

	void Drawable::SetScale(const Vector2f& new_scale)
	{
		m_scale = new_scale;
	}

	const Vector2i& Drawable::GetDimensions() const
	{
		return m_dimensions;
	}

	int Drawable::GetWidth() const
	{
		return m_dimensions.x;
	}

	int Drawable::GetHeight() const
	{
		return m_dimensions.y;
	}

	int Drawable::GetRotationInDeg() const
	{
		return m_rotation_in_deg;
	}

	const Vector2f& Drawable::GetScale() const
	{
		return m_scale;
	}
}