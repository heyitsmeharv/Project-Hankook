#pragma once

#include <SDL_render.h>

#include "Vector2.h"

namespace hk
{
	class Drawable
	{
	public:
				 Drawable();
		virtual ~Drawable();

		virtual void Draw() const = 0;

		virtual void SetRotation(int new_rot_in_deg);
		virtual void AddRotation(int delta_rot_in_deg);

		virtual void SetScale(float new_x_scale, float new_y_scale);
		virtual void SetScale(const Vector2f& new_scale);

		int				GetRotationInDeg() const;
		const Vector2f&	GetScale		() const;

	protected:
		int					m_rotation_in_deg;
		Vector2f			m_scale;
		SDL_RendererFlip	m_flip;
	};
}