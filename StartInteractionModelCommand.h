#pragma once

#include "InteractionTypes.h"
#include "ModelCommand.h"
#include "Vector2.h"


namespace hk
{
	class StartInteractionModelCommand : public ModelCommand
	{
	public:
		StartInteractionModelCommand(entt::entity interactor, entt::entity interactee, InteractionType type);

		void	Execute	(entt::registry& registry) override;

		int		Priority() const override { return 10; }

	private:
		entt::entity	m_interactor;
		entt::entity	m_interactee;
		InteractionType m_type;
	};
}