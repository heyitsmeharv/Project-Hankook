#pragma once

#include <string>
#include <SDL_render.h>
#include <unordered_map>

#include "Texture.h"

namespace hk
{
	class TextureManager
	{
	public:
		 TextureManager();
		~TextureManager();

		[[nodiscard]]
		bool Initialise(SDL_Renderer* renderer, const std::string& default_texture_path);
		void Destroy();

		[[nodiscard]]
		bool LoadTexture	(hk::TextureInitInfo& init_info);
		void LoadDirectory	(const std::string& path);

		[[nodiscard]]
		const hk::Texture& GetTexture(const std::string& filepath) const;
		
	private:
		SDL_Renderer*								m_renderer;
		std::unordered_map<std::string, Texture>	m_textures;
		Texture										m_default_texture;
	};
}