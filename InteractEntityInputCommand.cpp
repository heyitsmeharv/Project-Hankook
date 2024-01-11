#include "InteractEntityInputCommand.h"
#include "StartInteractionModelCommand.h"

#include <limits.h>

#include "Logger.h"
#include "GameModel.h"
#include "InteractionComponent.h"
#include "TransformComponent.h"

namespace hk
{
	std::unique_ptr<InputCommand> InteractEntityInputCommand::Clone() const
	{
		return std::make_unique<InteractEntityInputCommand>(*this);
	}

	void InteractEntityInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo&)
	{
	}

	void InteractEntityInputCommand::Execute(entt::entity /*controlled_entity*/, entt::entity, GameModel&) const
	{
		//const entt::registry& registry = GetGameModel().GetRegistry();
		//const TransformComponent& entity_transform = registry.get<TransformComponent>(controlled_entity);
		//
		//constexpr float interact_max_range = 64.0f * 64.0f;
		//float closest_distance = std::numeric_limits<float>::max();
		//entt::entity closest_entity = entt::null;
		//
		//auto view = registry.view<TransformComponent, InteractionComponent>();
		//view.each([&](entt::entity entity, const TransformComponent& transform, const InteractionComponent&)
		//{
		//	const float delta = (transform.position - entity_transform.position).MagnitudeSquared();
		//	if (delta < closest_distance && delta < interact_max_range)
		//	{
		//		closest_distance = delta;
		//		closest_entity = entity;
		//	}
		//});
		//
		//if (closest_entity != entt::null)
		//{		
		//	GetGameModel().QueueModelCommand(std::make_unique<StartInteractionModelCommand>(controlled_entity, closest_entity, registry.get<InteractionComponent>(closest_entity).type));
		//}
	}
}