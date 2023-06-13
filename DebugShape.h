#pragma once

#include <SDL_render.h>

struct SDL_Renderer;

namespace hk
{
	struct DebugRectInfo
	{
		int				x_pos;
		int				y_pos;
		int				width;
		int				height;
		SDL_Color		colour;
		SDL_Renderer*	renderer = nullptr;
	};

	class DebugRect
	{
	public:
		DebugRect(const DebugRectInfo& info);

		void Draw();

	private:
		SDL_Rect		m_rect;
		SDL_Color		m_colour;
		SDL_Renderer*	m_renderer;
	};

	struct DebugLineInfo
	{
		int				start_x_pos;
		int				start_y_pos;
		int				end_x_pos;
		int				end_y_pos;
		SDL_Color		colour;
		SDL_Renderer*	renderer = nullptr;
	};

	class DebugLine
	{
	public:
		DebugLine(const DebugLineInfo& info);

		void Draw();

	private:
		int				m_start_x_pos;
		int				m_start_y_pos;
		int				m_end_x_pos;
		int				m_end_y_pos;
		SDL_Color		m_colour;
		SDL_Renderer*	m_renderer;
	};

	struct DebugPointInfo
	{
		int				x_pos;
		int				y_pos;
		SDL_Color		colour;
		SDL_Renderer*	renderer = nullptr;
	};

	class DebugPoint
	{
	public:
		DebugPoint(const DebugPointInfo& info);

		void Draw();

	private:
		int				m_x_pos;
		int				m_y_pos;
		SDL_Color		m_colour;
		SDL_Renderer*	m_renderer;
	};
}