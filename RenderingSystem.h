#pragma once

#include <entt/fwd.hpp>
#include <SDL2/SDL_ttf.h>

namespace hk
{
	class Engine;

	class RenderingSystem
	{
	public:
		 RenderingSystem();
		~RenderingSystem();

		void Update(entt::registry& registry, entt::entity current_camera, Engine& engine) const;

		TTF_Font* GetFont() { return m_font; }

	private:
		TTF_Font* m_font;

	};
}