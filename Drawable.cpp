#include "Drawable.h"

namespace hk
{
	Drawable::Drawable()
		: m_x_pos(0)
		, m_y_pos(0)
		, m_x_scale(0)
		, m_y_scale(0)
		, m_rotation_in_deg(0)
		, m_flip(SDL_RendererFlip::SDL_FLIP_NONE)
	{
	}

	Drawable::~Drawable()
	{
	}

	void Drawable::SetPosition(int new_x_pos, int new_y_pos)
	{
		m_x_pos = new_x_pos;
		m_y_pos = new_y_pos;
	}

	void Drawable::MovePosition(int x_delta, int y_delta)
	{
		m_x_pos += x_delta;
		m_y_pos += y_delta;
	}

	void Drawable::SetRotation(int new_rot_in_deg)
	{
		m_rotation_in_deg = new_rot_in_deg;
	}

	void Drawable::AddRotation(int delta_rot_in_deg)
	{
		m_rotation_in_deg += delta_rot_in_deg;
	}

}