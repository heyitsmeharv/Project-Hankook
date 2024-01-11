#include "RenderingSystem.h"

#include <entt/entt.hpp>

#include "Engine.h"
#include "CameraComponent.h"
#include "SpriteComponent.h"
#include "SetRenderScaleDrawRequest.h"
#include "TextComponent.h"
#include "Texture.h"
#include "TextureDrawRequest.h"
#include "TileDrawRequest.h"
#include "TilemapComponent.h"
#include "TransformComponent.h"
#include "UIComponent.h"

namespace hk
{
	RenderingSystem::RenderingSystem()
		: m_font(nullptr)
	{
		m_font = TTF_OpenFont("Data\\Fonts\\DejaVuSans.ttf", 28);
	}

	RenderingSystem::~RenderingSystem()
	{
		//TTF_CloseFont(m_font);
		m_font = nullptr;
	}

	void RenderingSystem::Update(entt::registry& registry, entt::entity current_camera, Engine& engine) const
	{
		const TransformComponent& camera_transform = registry.get<TransformComponent>(current_camera);
		const CameraComponent& camera_info = registry.get<CameraComponent>(current_camera);

		// Set render scale from camera
		{
			std::unique_ptr<hk::SetRenderScaleDrawRequest> scale_request = std::make_unique<SetRenderScaleDrawRequest>();
			scale_request->renderer = engine.GameWindow().GetRenderer();
			scale_request->scale = { camera_info.zoom, camera_info.zoom };
			scale_request->z_index = -INT_MAX;	//Hacky af but makes sure this is done first

			engine.AddDrawRequest(std::move(scale_request));
		}

		auto tilemap_view = registry.view<const TilemapComponent>();
		tilemap_view.each([&](const TilemapComponent& tilemap)
		{
			for (const auto& layer : tilemap.layers)
			{
				engine.AddDrawRequest(layer->CreateDrawRequest(tilemap.tilesets[0], { (int)camera_transform.position.x, (int)camera_transform.position.y }, camera_info.zoom));
			}
		});

		auto sprite_view = registry.view<SpriteComponent, const TransformComponent>();
		sprite_view.each([&](SpriteComponent& sprite, const TransformComponent& transform)
		{
			if(sprite.texture == nullptr)
			{
				sprite.texture = &engine.GetTextureManager().GetTexture("Data\\" + sprite.asset_id);
			}

			std::unique_ptr<hk::TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

			draw_request->z_index = sprite.z_index;
			draw_request->texture = sprite.texture;
			draw_request->draw_info.position = { (int)transform.position.x, (int)transform.position.y };
			draw_request->draw_info.angle_in_deg = sprite.angle_in_deg;
			draw_request->draw_info.flip = sprite.flip;
			draw_request->draw_info.centre = sprite.centre;
			draw_request->draw_info.dimensions = sprite.dimensions;
			draw_request->draw_info.colour_mod = sprite.colour_mod;
			draw_request->draw_info.scale = sprite.scale * camera_info.zoom;
			draw_request->draw_info.viewport_rect = SDL_Rect{ (int)camera_transform.position.x, (int)camera_transform.position.y, camera_info.dimensions.x, camera_info.dimensions.y };

			engine.AddDrawRequest(std::move(draw_request));
		});

		auto text_view = registry.view<const TextComponent, const TransformComponent>();
		text_view.each([&](const TextComponent& text, const TransformComponent& transform)
		{
			std::unique_ptr<hk::TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

			draw_request->z_index = text.z_index;
			draw_request->texture = &text.texture;
			draw_request->draw_info.position = { (int)transform.position.x, (int)transform.position.y };
			draw_request->draw_info.angle_in_deg = text.angle_in_deg;
			draw_request->draw_info.flip = text.flip;
			draw_request->draw_info.centre = text.centre;
			draw_request->draw_info.dimensions = text.dimensions;
			draw_request->draw_info.scale = text.scale * camera_info.zoom;
			draw_request->draw_info.viewport_rect = SDL_Rect{ (int)camera_transform.position.x, (int)camera_transform.position.y, camera_info.dimensions.x, camera_info.dimensions.y };

			engine.AddDrawRequest(std::move(draw_request));
		});

		auto ui_view = registry.view<ui::UIComponent>();
		ui_view.each([&](ui::UIComponent& ui_element)
		{
			const auto& itr = ui_element.states.find(ui_element.current_state);
			if (itr != ui_element.states.end())
			{
				ui::UIComponentState& state = itr->second;

				//Draw state images (if we have any)
				for (int i = 0; i < static_cast<int>(state.asset_ids.size()); ++i)
				{
					if ((int)state.m_image_textures.size() - 1 < i)
					{
						state.m_image_textures.push_back(nullptr);
					}

					if(state.m_image_textures[i] == nullptr)
					{
						state.m_image_textures[i] = &engine.GetTextureManager().GetTexture("Data\\" + state.asset_ids[i]);
					}

					std::unique_ptr<hk::TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

					draw_request->draw_info.position = { (int)ui_element.position.x, (int)ui_element.position.y };
					draw_request->draw_info.dimensions = ui_element.dimensions;
					draw_request->z_index = ui_element.z_index;
					draw_request->texture = state.m_image_textures[i];
					draw_request->draw_info.flip = state.flip_texture;
					draw_request->draw_info.colour_mod = state.colour_mod;
					draw_request->draw_info.centre = std::nullopt;
					draw_request->draw_info.viewport_rect = std::nullopt;

					engine.AddDrawRequest(std::move(draw_request));
				}

				//Draw text (if we have any)
				if (state.text.empty() == false)
				{
					std::unique_ptr<hk::TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

					if (state.m_is_text_dirty)
					{
						TextureInitInfo init_info;
						init_info.renderer = engine.GameWindow().GetRenderer();

						state.m_text_texture = Texture(init_info);
						if (state.m_text_texture.CreateTextureFromText(m_font, state.text, state.text_colour) == false)
						{
							hk::Fault(hk::ErrorCategory::GFX, "state text texture creation failed");
						}
						state.m_is_text_dirty = false;
					}

					draw_request->draw_info.position = { (int)ui_element.position.x, (int)ui_element.position.y };
					draw_request->z_index = ui_element.z_index;
					draw_request->texture = &state.m_text_texture;	//this seems really dangerous as we own the texture... maybe we should let the texture manager handle this shit

					engine.AddDrawRequest(std::move(draw_request));
				}
			}
		});
	}
}