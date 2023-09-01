#pragma once

#include <SDL_rect.h>
#include <vector>
#include <optional>
#include <memory>

#include "Transformable.h"
#include "Vector2.h"

namespace hk
{
	class CameraAttachment;

	struct CameraInitInfo
	{
		Vector2f					position;
		Vector2i					dimensions;
	};

	class Camera : public Transformable
	{
	public:
				 Camera();
				 Camera(const CameraInitInfo& init_info);
		virtual ~Camera();

		void			ChangeDimensions(const Vector2i& delta);
		void			SetDimensions	(const Vector2i& new_dims);

		const Vector2i& GetDimensions	() const;
		SDL_Rect		GetCameraRect	() const;

		void			AddAttachment	(std::unique_ptr<CameraAttachment>&& attachment);
		
		virtual void	Update			();

		virtual void	SetPosition		(float new_x_pos, float new_y_pos) override;
		virtual void	SetPosition		(const Vector2f& new_pos) override;

		virtual void	MovePosition	(float x_delta, float y_delta) override;
		virtual void	MovePosition	(const Vector2f& delta) override;

	protected:
		Vector2i										m_dimensions;
		std::vector<std::unique_ptr<CameraAttachment>>	m_attachments;
	};
}