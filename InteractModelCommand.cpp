#include "InteractModelCommand.h"
#include "GameObject.h"

namespace hk
{
	InteractModelCommand::InteractModelCommand(GameObject& game_object)
		: m_game_object(&game_object)
	{
	}

	void InteractModelCommand::Execute()
	{
		if (m_game_object)
		{
			auto filter_func = [](GameObject* game_object) -> bool
			{
				return game_object->IsInteractable();
			};

			GameObject* closest_obj = m_game_object->FindClosestGameObject(filter_func);
			if (closest_obj)
			{
				const float distance = (closest_obj->GetPosition() - m_game_object->GetPosition()).MagnitudeSquared();
				if (distance <= (m_game_object->InteractableRange() * m_game_object->InteractableRange()))
				{
					closest_obj->OnInteraction(*m_game_object);
				}
			}
		}
	}
}