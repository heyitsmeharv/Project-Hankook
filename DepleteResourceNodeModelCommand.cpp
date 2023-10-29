#include "DepleteResourceNodeModelCommand.h"
#include "NodeResourceGameObject.h"

namespace hk
{
	DepleteResourceNodeModelCommand::DepleteResourceNodeModelCommand(NodeResourceGameObject& node_resource, int decrement_amount)
		: m_node_resource(&node_resource)
		, m_decrement_amount(decrement_amount)
	{
	}

	void DepleteResourceNodeModelCommand::Execute()
	{
		if (m_node_resource)
		{
			m_node_resource->DecrementStage();
		}
	}
}