#pragma once

#include <SDL_rect.h>
#include <optional>

#include "Transformable.h"
#include "Vector2.h"

namespace hk
{
	struct CameraInitInfo
	{
		Vector2f					position;
		Vector2i					dimensions;
		std::optional<SDL_FRect>	contraints;
	};

	class Camera : public Transformable
	{
	public:
		Camera(const CameraInitInfo& init_info);

		void			ChangeDimensions(const Vector2i& delta);
		void			SetDimensions	(const Vector2i& new_dims);

		const Vector2i& GetDimensions	() const;
		SDL_Rect		GetCameraRect	() const;

		virtual void SetPosition(float new_x_pos, float new_y_pos) override;
		virtual void SetPosition(const Vector2f& new_pos) override;

		virtual void MovePosition(float x_delta, float y_delta) override;
		virtual void MovePosition(const Vector2f& delta) override;

	protected:
		void ClampToConstraint();

	protected:
		Vector2i					m_dimensions;
		std::optional<SDL_FRect>	m_constraints;
	};
}