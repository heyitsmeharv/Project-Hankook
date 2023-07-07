#pragma once

#include "Vector2.h"

namespace hk
{ 
	class Transformable
	{
	public:
				 Transformable();
				 Transformable(const Vector2i& position);
		virtual ~Transformable();

		virtual void SetPosition(int new_x_pos, int new_y_pos);
		virtual void SetPosition(const Vector2i& new_pos);

		virtual void MovePosition(int x_delta, int y_delta);
		virtual void MovePosition(const Vector2i& delta);

	protected:
		Vector2i m_position;
	};
}