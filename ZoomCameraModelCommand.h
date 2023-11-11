#pragma once

#include "ModelCommand.h"

namespace hk
{
	class ZoomCameraModelCommand : public ModelCommand
	{
	public:
		ZoomCameraModelCommand(entt::entity entity, const float delta);

		void Execute(entt::registry& registry) override;

	private:
		entt::entity	m_entity;
		float			m_delta;
	};
}