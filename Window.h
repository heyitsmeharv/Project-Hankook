#pragma once

#include <string>
#include <SDL_video.h>
#include <SDL_render.h>

namespace hk
{
	struct WindowInitData
	{
		std::string window_title;
		int			x_pos = SDL_WINDOWPOS_UNDEFINED;
		int			y_pos = SDL_WINDOWPOS_UNDEFINED;
		int			width = 800;
		int			height = 800;
		SDL_Color	draw_colour = { 0xFF, 0xFF, 0xFF, 0xFF };
		SDL_Color	clear_colour = { 0xFF, 0xFF, 0xFF, 0xFF };
		Uint32		flags;
	};

	class Window
	{
	public:
		 Window(const WindowInitData& init_data);
		~Window();

		bool Create(const WindowInitData& init_data);
		void Destroy();

		void Clear();
		void Display();

		bool IsValid() const;

		SDL_Window*		GetWindow();
		SDL_Renderer*	GetRenderer();

	private:
		SDL_Window*		m_window;
		SDL_Renderer*	m_renderer;

		SDL_Color		m_clear_colour;
		SDL_Color		m_draw_colour;
	};
}