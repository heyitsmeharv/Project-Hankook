#include "ChangeResourceAmountModelCommand.h"
#include "GameObject.h"
#include "Resource.h"

namespace hk
{
	ChangeResourceAmountModelCommand::ChangeResourceAmountModelCommand(GameObject& game_object, const std::string& resource_key, const double delta)
		: m_game_object(&game_object)
		, m_resource_key(resource_key)
		, m_delta(delta)
	{
	}

	void ChangeResourceAmountModelCommand::Execute()
	{
		if (m_game_object)
		{
			Resource* resource = m_game_object->GetResource(m_resource_key);
			if (resource)
			{
				resource->ChangeAmount(m_delta);
			}
		}
	}
}