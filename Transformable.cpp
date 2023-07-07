#include "Transformable.h"

namespace hk
{
	Transformable::Transformable()
		: m_position()
	{
	}

	Transformable::Transformable(const Vector2i& position)
		: m_position(position)
	{
	}

	Transformable::~Transformable()
	{
	}

	void Transformable::SetPosition(int new_x_pos, int new_y_pos)
	{
		m_position.x = new_x_pos;
		m_position.y = new_y_pos;
	}

	void Transformable::SetPosition(const Vector2i& new_pos)
	{
		m_position = new_pos;
	}

	void Transformable::MovePosition(int x_delta, int y_delta)
	{
		m_position.x += x_delta;
		m_position.y += y_delta;
	}

	void Transformable::MovePosition(const Vector2i& delta)
	{
		m_position += delta;
	}
}