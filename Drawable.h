#pragma once

#include <memory>
#include <SDL2/SDL_render.h>

#include "Vector2.h"
#include "EngineAccess.h"

namespace hk
{
	struct DrawRequest;

	class Drawable
	{
	public:
				 Drawable();
		virtual ~Drawable();

		virtual void	Draw			() const = 0;

		virtual void	SetDimensions	(const Vector2i& new_dimensions);
		virtual void	SetWidth		(const int width);
		virtual void	SetHeight		(const int height);

		virtual void	SetRotation		(int new_rot_in_deg);
		virtual void	AddRotation		(int delta_rot_in_deg);

		virtual void	SetScale		(float new_x_scale, float new_y_scale);
		virtual void	SetScale		(const Vector2f& new_scale);

		const Vector2i& GetDimensions	() const;
		int				GetWidth		() const;
		int				GetHeight		() const;
		int				GetRotationInDeg() const;
		const Vector2f&	GetScale		() const;

	protected:
		void			AddDrawToQueue(std::unique_ptr<DrawRequest>&& draw_request) const;

	protected:
		int					m_rotation_in_deg;
		Vector2i			m_dimensions;
		Vector2f			m_scale;
		SDL_RendererFlip	m_flip;
	};
}