#include "StartInteractionModelCommand.h"

#include <entt/entt.hpp>

namespace hk
{
	StartInteractionModelCommand::StartInteractionModelCommand(entt::entity interactor, entt::entity interactee, InteractionType type)
		: m_interactor(interactor)
		, m_interactee(interactee)
		, m_type(type)
	{
	}

	void StartInteractionModelCommand::Execute(entt::registry&)
	{
		//GetGameModel().PushNewInteraction(PendingInteraction{ m_interactor, m_interactee, m_type });
	}
}