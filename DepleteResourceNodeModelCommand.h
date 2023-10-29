#pragma once

#include "ModelCommand.h"

namespace hk
{
	class NodeResourceGameObject;

	class DepleteResourceNodeModelCommand : public ModelCommand
	{
	public:
		DepleteResourceNodeModelCommand(NodeResourceGameObject& node_resource, int decrement_amount = 1);

		void Execute() override;

	private:
		NodeResourceGameObject* m_node_resource = nullptr;
		int						m_decrement_amount;
	};
}