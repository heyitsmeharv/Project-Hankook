#pragma once

#include <entt/fwd.hpp>
#include <queue>

#include "InteractionTypes.h"

namespace hk
{
	struct PendingInteraction
	{
		entt::entity	interator;
		entt::entity	interactee;
		InteractionType type;
	};

	class InteractionSystem
	{
	public:
		void Update(entt::registry& registry);

		void PushNewInteraction			(const PendingInteraction& new_interaction);
		void FinishCurrentInteraction	();

		const PendingInteraction* CurrentInteraction() const;

	private:
		std::queue<PendingInteraction>	m_pending_interactions;
		PendingInteraction*				m_current_interaction = nullptr;
	};
}