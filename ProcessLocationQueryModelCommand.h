#pragma once

#include "ModelCommand.h"
#include "Vector2.h"

namespace hk
{
	class ProcessLocationQueryModelCommand : public ModelCommand
	{
	public:
		ProcessLocationQueryModelCommand(const std::vector<Vector2i>& cell_list, entt::entity grid_entity);

		void Execute(entt::registry& registry) override;

	private:
		std::vector<Vector2i>	m_cell_list;
		entt::entity			m_grid_entity;
	};
}