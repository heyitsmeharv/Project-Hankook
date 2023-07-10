#include "Texture.h"

#include <SDL_image.h>
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
		if (info.clip.has_value())
		{
			render_quad.w = info.clip->w;
			render_quad.h = info.clip->h;
		}
		
		SDL_RenderCopyEx(   m_renderer, 
							m_texture, 
							info.clip.has_value() ? &info.clip.value() : nullptr, 
							&render_quad, 
							info.angle_in_deg, 
							info.centre.has_value() ? &info.centre.value() : nullptr, 
							info.flip);
	}
}