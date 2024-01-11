#include "ControllerSystem.h"
#include "PlayerControllerComponent.h"
#include "ControllerInstance.h"

#include "InputCommand.h"

#include <entt/entt.hpp>

namespace hk
{
	void ControllerSystem::Update(entt::registry& registry, GameModel& model) const
	{
		auto controller_view = registry.view<PlayerControllerComponent>();
		controller_view.each([&](PlayerControllerComponent& controller)
		{
			if (controller.controlled_entity != entt::null)
			{
				std::vector<std::unique_ptr<InputCommand>> command_list = controller.controller->Update();
				for (auto& command : command_list)
				{
					command->Execute(controller.controlled_entity, controller.controlled_camera, model);
				}
			}
		});
	}
}