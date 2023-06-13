#include "Window.h"

#include <SDL_image.h>

namespace hk
{
	Window::Window(const WindowInitData& init_data)
	{
        Create(init_data);
	}

    bool Window::Create(const WindowInitData& init_data)
    {
        m_window = SDL_CreateWindow(init_data.window_title.data(), init_data.x_pos, init_data.y_pos, init_data.width, init_data.height, init_data.flags);
        if (m_window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (m_renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            else
            {
                m_clear_colour = init_data.clear_colour;
                m_draw_colour = init_data.draw_colour;

                SDL_SetRenderDrawColor(m_renderer, init_data.clear_colour.r, init_data.clear_colour.g, init_data.clear_colour.b, init_data.clear_colour.a);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    return false;
                }
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

    void Window::Clear()
    {
        SDL_SetRenderDrawColor(m_renderer, m_clear_colour.r, m_clear_colour.g, m_clear_colour.b, m_clear_colour.a);
        SDL_RenderClear(m_renderer);
    }

    void Window::Display()
    {
        SDL_RenderPresent(m_renderer);
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