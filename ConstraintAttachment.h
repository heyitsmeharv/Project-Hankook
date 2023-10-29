#pragma once

#include "CameraAttachment.h"

#include <SDL2/SDL_rect.h>

namespace hk
{
	class Transformable;

	class ConstraintAttachment final : public CameraAttachment
	{
	public:
		ConstraintAttachment();
		ConstraintAttachment(const SDL_FRect& constraint);

		void Update(Camera& camera) override;

		void SetConstraint(const SDL_FRect& constraint);

	private:
		SDL_FRect	m_constraint;
	};
}