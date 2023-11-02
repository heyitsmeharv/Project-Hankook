#include "RenderingSystem.h"

#include <entt/entt.hpp>

#include "Engine.h"
#include "EngineAccess.h"
#include "CameraComponent.h"
#include "SpriteComponent.h"
#include "TilemapComponent.h"
#include "TransformComponent.h"
#include "Texture.h"
#include "TextureDrawRequest.h"

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

		auto sprite_view = registry.view<const SpriteComponent, const TransformComponent>();
		sprite_view.each([&](const SpriteComponent& sprite, const TransformComponent& transform)
		{
			if (sprite.texture)
			{
				std::unique_ptr<hk::TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

				draw_request->texture = sprite.texture;
				draw_request->draw_info.position = { (int)transform.position.x, (int)transform.position.y };
				draw_request->draw_info.angle_in_deg = sprite.angle_in_deg;
				draw_request->draw_info.flip = sprite.flip;
				draw_request->draw_info.centre = sprite.centre;
				draw_request->draw_info.dimensions = sprite.dimensions;
				draw_request->draw_info.colour_mod = sprite.colour_mod;
				draw_request->draw_info.scale = sprite.scale * camera_info.zoom;
				draw_request->draw_info.viewport_rect = SDL_Rect{ (int)camera_transform.position.x, (int)camera_transform.position.y, camera_info.dimensions.x, camera_info.dimensions.y };

				GetEngine().AddDrawRequest(std::move(draw_request));
			}
		});
	}
}