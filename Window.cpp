#include "Window.h"

#include "ErrorManager.h"

namespace hk
{
	Window::Window(const WindowInitInfo& init_info)
		: m_window_id(0)
		, m_is_minimised(false)
	{
		Create(init_info);
	}

	Window::Window(Window&& rhs)
	{
		m_window = rhs.m_window;
		m_window_id = rhs.m_window_id;
		m_renderer = rhs.m_renderer;
		m_is_minimised = rhs.m_is_minimised;

		m_clear_colour = rhs.m_clear_colour;
		m_draw_colour = rhs.m_draw_colour;

		rhs.m_window = nullptr;
		rhs.m_window_id = 0;
		rhs.m_renderer = nullptr;
	}

	Window& Window::operator=(Window&& rhs)
	{
		m_window = std::move(rhs.m_window);
		m_window_id = std::move(rhs.m_window_id);
		m_renderer = std::move(rhs.m_renderer);
		m_is_minimised = rhs.m_is_minimised;

		m_clear_colour = rhs.m_clear_colour;
		m_draw_colour = rhs.m_draw_colour;

		return *this;
	}

	bool Window::Create(const WindowInitInfo& init_info)
	{
		m_window = SDL_CreateWindow(init_info.window_title.data(), init_info.x_pos, init_info.y_pos, init_info.width, init_info.height, init_info.flags);
		if (m_window == nullptr)
		{
			hk::Warn(hk::ErrorCategory::GFX, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_renderer == NULL)
			{
				hk::Warn(hk::ErrorCategory::GFX, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				m_window_id = SDL_GetWindowID(m_window);

				m_clear_colour = init_info.clear_colour;
				m_draw_colour = init_info.draw_colour;

				SDL_SetRenderDrawColor(m_renderer, init_info.clear_colour.r, init_info.clear_colour.g, init_info.clear_colour.b, init_info.clear_colour.a);
			}
		}

		return true;
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Destroy()
	{
		if (IsValid())
		{
			SDL_DestroyRenderer(m_renderer);
			m_renderer = nullptr;

			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}
	}

	void Window::ProcessEvent(const SDL_Event& e)
	{
		//If an event was detected for this window
		if (e.type == SDL_WINDOWEVENT && e.window.windowID == m_window_id)
		{
			switch (e.window.event)
			{
				//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
				break;

				//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
				break;

				//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				break;

				//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(m_renderer);
				break;

				//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
				break;

				//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
				break;

				//Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				break;

				//Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
				break;

				//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				m_is_minimised = true;
				break;

				//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
				m_is_minimised = false;
				break;

				//Window restored
			case SDL_WINDOWEVENT_RESTORED:
				m_is_minimised = false;
				break;

				//Hide on close
			case SDL_WINDOWEVENT_CLOSE:

				break;
			}
		}
	}

	void Window::Focus() const
	{
		SDL_RaiseWindow(m_window);
	}

	void Window::Clear()
	{
		SDL_SetRenderDrawColor(m_renderer, m_clear_colour.r, m_clear_colour.g, m_clear_colour.b, m_clear_colour.a);
		SDL_RenderClear(m_renderer);
	}

	void Window::Display()
	{
		if (m_is_minimised == false)
		{
			SDL_RenderPresent(m_renderer);
		}
	}

	Vector2i Window::GetWindowDimensions() const
	{
		SDL_Surface* surface = SDL_GetWindowSurface(m_window);
		if (surface)
		{
			return { surface->w, surface->h };
		}

		return { -1, -1 };
	}

	SDL_Window* Window::GetWindow()
	{
		return m_window;
	}

	SDL_Renderer* Window::GetRenderer()
	{
		return m_renderer;
	}

	bool Window::IsValid() const
	{
		return m_window != nullptr && m_renderer != nullptr;
	}
}