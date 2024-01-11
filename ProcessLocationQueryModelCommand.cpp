#include "ProcessLocationQueryModelCommand.h"

#include <entt/entt.hpp>
#include "GridComponent.h"

#include "WordSearchModel.h"
#include "WordSearchModelAccess.h"
#include "WordFoundEvent.h"

namespace hk
{
	ProcessLocationQueryModelCommand::ProcessLocationQueryModelCommand(const std::vector<Vector2i>& cell_list, entt::entity grid_entity)
		: m_cell_list(cell_list)
		, m_grid_entity(grid_entity)
	{
	}

	void ProcessLocationQueryModelCommand::Execute(entt::registry& registry)
	{
		GridComponent* grid_component = registry.try_get<GridComponent>(m_grid_entity);
		if (grid_component) 
		{
			for (auto& [word, word_info] : grid_component->word_infos)
			{
				if (word_info.is_found == false && word_info.locations == m_cell_list)
				{
					registry.patch<GridComponent>(m_grid_entity, [&word](auto& grid) { grid.word_infos.at(word).is_found = true; });
					registry.ctx().get<WordSearchModelAccess>().model_access->OnWordFound(word, std::move(m_cell_list));
					break;
				}
			}
		}
	}
}