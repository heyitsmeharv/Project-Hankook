#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

#include "Vector2.h"

namespace hk
{
	struct WindowInitInfo
	{
		std::string window_title;
		int			x_pos = SDL_WINDOWPOS_UNDEFINED;
		int			y_pos = SDL_WINDOWPOS_UNDEFINED;
		int			width = 800;
		int			height = 800;
		SDL_Color	draw_colour = { 255, 255, 255, 255 };
		SDL_Color	clear_colour = { 255, 255, 255, 255 };
		Uint32		flags;
	};

	class Window
	{
	public:
		 Window(const WindowInitInfo& init_info);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&& rhs);
		Window& operator=(Window&& rhs);

		bool Create(const WindowInitInfo& init_info);
		void Focus() const;
		void Destroy();

		void ProcessEvent(const SDL_Event& e);

		void Clear();
		void Display();

		bool IsValid() const;

		Vector2i GetWindowDimensions() const;

		SDL_Window*		GetWindow();
		SDL_Renderer*	GetRenderer();

	private:
		SDL_Window*		m_window;
		Uint32			m_window_id;
		SDL_Renderer*	m_renderer;
		bool			m_is_minimised;

		SDL_Color		m_clear_colour;
		SDL_Color		m_draw_colour;
	};
}