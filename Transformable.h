#pragma once

#include "Vector2.h"

namespace hk
{ 
	class Transformable
	{
	public:
				 Transformable();
				 Transformable(const Vector2f& position);
		virtual ~Transformable();

		const Vector2f& GetPosition() const;

		virtual void SetPosition(float new_x_pos, float new_y_pos);
		virtual void SetPosition(const Vector2f& new_pos);

		virtual void MovePosition(float x_delta, float y_delta);
		virtual void MovePosition(const Vector2f& delta);

	protected:
		Vector2f m_position;
	};
}