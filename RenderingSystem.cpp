#include "RenderingSystem.h"

#include <entt/entt.hpp>

#include "CameraComponent.h"
#include "TilemapComponent.h"
#include "TransformComponent.h"

namespace hk
{
	void RenderingSystem::Update(entt::registry& registry, entt::entity current_camera) const
	{
		const TransformComponent& camera_transform = registry.get<TransformComponent>(current_camera);
		const CameraComponent& camera_info = registry.get<CameraComponent>(current_camera);

		auto tilemap_view = registry.view<const TilemapComponent>();
		tilemap_view.each([&](const TilemapComponent& tilemap)
		{
			for (const auto& layer : tilemap.layers)
			{
				layer->Draw(tilemap.tilesets[0], { (int)camera_transform.position.x, (int)camera_transform.position.y }, camera_info.zoom);
			}
		});
	}
}