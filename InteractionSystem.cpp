#include "InteractionSystem.h"

namespace hk
{
	void InteractionSystem::Update(entt::registry&)
	{
		if (m_current_interaction != nullptr && m_pending_interactions.empty() == false)
		{
			m_current_interaction = &m_pending_interactions.front();

			switch (m_current_interaction->type)
			{
				case InteractionType::DIALOGUE:
				{

					break;
				}
				case InteractionType::LOOT:
				{
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	void InteractionSystem::PushNewInteraction(const PendingInteraction& new_interaction)
	{
		m_pending_interactions.push(new_interaction);
	}

	void InteractionSystem::FinishCurrentInteraction()
	{
		m_pending_interactions.pop();
	}

	const PendingInteraction* InteractionSystem::CurrentInteraction() const
	{
		return m_current_interaction;
	}
}