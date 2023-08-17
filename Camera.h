#pragma once

#include <SDL_rect.h>

#include "Transformable.h"
#include "Vector2.h"

namespace hk
{
	struct CameraInitInfo
	{
		Vector2f position;
		Vector2i dimensions;
	};

	class Camera : public Transformable
	{
	public:
		Camera(const CameraInitInfo& init_info);

		void			ChangeDimensions(const Vector2i& delta);
		void			SetDimensions	(const Vector2i& new_dims);

		const Vector2i& GetDimensions	() const;
		SDL_Rect		GetCameraRect	() const;

	protected:
		Vector2i m_dimensions;
	};
}