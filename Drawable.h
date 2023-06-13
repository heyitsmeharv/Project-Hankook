#pragma once

#include <SDL_render.h>

namespace hk
{
	class Drawable
	{
	public:
				 Drawable();
		virtual ~Drawable();

		virtual void Draw() const = 0;

		virtual void SetPosition(int new_x_pos, int new_y_pos);
		virtual void MovePosition(int x_delta, int y_delta);

		virtual void SetRotation(int new_rot_in_deg);
		virtual void AddRotation(int delta_rot_in_deg);

	protected:
		int m_x_pos;
		int m_y_pos;

		int m_x_scale;
		int m_y_scale;

		int m_rotation_in_deg;

		SDL_RendererFlip m_flip;
	};
}