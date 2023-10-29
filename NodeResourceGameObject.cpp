#include "NodeResourceGameObject.h"
#include "ChangeResourceAmountModelCommand.h"
#include "DepleteResourceNodeModelCommand.h"
#include "GameModelAccess.h"
#include "GameModel.h"

namespace hk
{
	NodeResourceGameObject::NodeResourceGameObject(NodeResourceGameObjectInitInfo& init_info)
		: GameObject(init_info)
		, m_stages(init_info.stages)
		, m_current_stage(init_info.starting_stage)
	{
	}

	NodeResourceGameObject::~NodeResourceGameObject()
	{
	}

	void NodeResourceGameObject::OnInteraction(GameObject& interacting_obect)
	{
		GetGameModel().QueueModelCommand(std::make_unique<ChangeResourceAmountModelCommand>(interacting_obect, CurrentStage().resource_key, CurrentStage().amount_on_change));
		GetGameModel().QueueModelCommand(std::make_unique<DepleteResourceNodeModelCommand>(*this));
	}

	void NodeResourceGameObject::DecrementStage()
	{
		if (m_current_stage > 0)
		{
			--m_current_stage;
		}
	}

	const NodeStage& NodeResourceGameObject::CurrentStage() const
	{
		return m_stages[m_current_stage];
	}
}