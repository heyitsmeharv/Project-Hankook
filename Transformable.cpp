#include "Transformable.h"

namespace hk
{
	Transformable::Transformable()
		: m_position()
	{
	}

	Transformable::Transformable(const Vector2f& position)
		: m_position(position)
	{
	}

	Transformable::~Transformable()
	{
	}

	const Vector2f& Transformable::GetPosition() const
	{
		return m_position;
	}

	void Transformable::SetPosition(float new_x_pos, float new_y_pos)
	{
		m_position.x = new_x_pos;
		m_position.y = new_y_pos;
	}

	void Transformable::SetPosition(const Vector2f& new_pos)
	{
		m_position = new_pos;
	}

	void Transformable::MovePosition(float x_delta, float y_delta)
	{
		m_position.x += x_delta;
		m_position.y += y_delta;
	}

	void Transformable::MovePosition(const Vector2f& delta)
	{
		m_position += delta;
	}
}