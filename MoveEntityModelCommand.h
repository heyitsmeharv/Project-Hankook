#pragma once

#include "ModelCommand.h"
#include "Vector2.h"

namespace hk
{
	class MoveEntityModelCommand : public ModelCommand
	{
	public:
		MoveEntityModelCommand(entt::entity entity, const Vector2f delta);

		void Execute(entt::registry& registry) override;

	private:
		entt::entity	m_entity;
		Vector2f		m_delta;
	};
}