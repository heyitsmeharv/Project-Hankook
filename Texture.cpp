#include "Texture.h"

#include <SDL2/SDL_image.h>
#include "ErrorManager.h"

namespace hk
{
	Texture::Texture()
		: m_filepath()
		, m_keyed_colour()
		, m_renderer(nullptr)
		, m_texture(nullptr)
		, m_width(0)
		, m_height(0)
	{
	}

	Texture::Texture(const TextureInitInfo& info)
		: m_filepath(info.filepath)
		, m_keyed_colour(info.keyed_colour)
		, m_renderer(info.renderer)
		, m_texture(nullptr)
		, m_width(0)
		, m_height(0)
	{
	}

	Texture::~Texture()
	{
		Destroy();
	}

	void Texture::Destroy()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;

			//We do not own the renderer only have a ptr to it so just null it
			m_renderer = nullptr;
		}
	}

	bool Texture::LoadTexture()
	{
		SDL_Surface* image_surface = IMG_Load(m_filepath.data());
		if (image_surface == nullptr)
		{
			hk::Warn(hk::ErrorCategory::GFX, "Unable to load Texture %s! SDL Error: %s\n", m_filepath.data(), SDL_GetError());
			return false;
		}
		else
		{
			m_width = image_surface->w;
			m_height = image_surface->h;

			if (m_keyed_colour.has_value())
			{
				SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, m_keyed_colour->r, m_keyed_colour->g, m_keyed_colour->b));
			}

			m_texture = SDL_CreateTextureFromSurface(m_renderer, image_surface);
			hk::WarnIf::Null(m_texture, hk::ErrorCategory::GFX, "Unable to create texture from %s! SDL Error: %s\n", m_filepath.c_str(), SDL_GetError());

			SDL_FreeSurface(image_surface);
		}

		return true;
	}

	void Texture::Draw(const TextureDrawInfo& info) const
	{
		SDL_Rect render_quad{ info.position.x, info.position.y, info.dimensions.x, info.dimensions.y };
		if (info.dimensions.IsZeroed())
		{
			render_quad.w = GetWidth();
			render_quad.h = GetHeight();
		}

		if (info.clip.has_value())
		{
			render_quad.w = info.clip->w;
			render_quad.h = info.clip->h;
		}

		if (info.viewport_rect.has_value())
		{
			// If the texture is out of the camera rect, don't render it
			if (SDL_HasIntersection(&info.viewport_rect.value(), &render_quad) == false)
			{
				return;
			}
			else
			{
				render_quad.x -= info.viewport_rect->x;
				render_quad.y -= info.viewport_rect->y;
			}
		}

		SDL_Color current_colour{};

		if (info.colour_mod.has_value())
		{
			SDL_GetTextureColorMod(m_texture, &current_colour.r, &current_colour.g, &current_colour.b);
			SDL_SetTextureColorMod(m_texture, info.colour_mod->r, info.colour_mod->g, info.colour_mod->b);
		}
		
		SDL_RenderCopyEx(   m_renderer,
							m_texture,
							info.clip.has_value() ? &info.clip.value() : nullptr,
							&render_quad,
							info.angle_in_deg,
							info.centre.has_value() ? &info.centre.value() : nullptr,
							info.flip);

		if (info.colour_mod.has_value())
		{
			SDL_SetTextureColorMod(m_texture, current_colour.r, current_colour.g, current_colour.b);
		}
	}

	void Texture::DrawTiles(const TileDrawInfo& info) const
	{
		if (info.vertices == nullptr)
		{
			return;
		}

		std::vector<SDL_Vertex> offset_verts = *info.vertices;

		// Intentional copy so we can offset them... not a big fan of this approach but cannot think of anything better
		for (auto& vert : offset_verts)
		{
			vert.position.x -= info.offset->x;
			vert.position.y -= info.offset->y;
		}

		SDL_RenderGeometry(m_renderer, m_texture, offset_verts.data(), (int)offset_verts.size(), info.indices ? info.indices->data() : nullptr, info.indices ? (int)info.indices->size() : 0);
	}
}