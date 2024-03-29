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

		void Update(entt::entity camera_entity, entt::registry& registry) override;

		void SetConstraint(const SDL_FRect& constraint);

	private:
		SDL_FRect	m_constraint;
	};
}