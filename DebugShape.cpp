#include "DebugShape.h"

namespace hk
{
	DebugRect::DebugRect(const DebugRectInfo& info)
		: m_colour(info.colour)
		, m_renderer(info.renderer)
	{
		m_rect.x = info.x_pos;
		m_rect.y = info.y_pos;
		m_rect.w = info.width;
		m_rect.h = info.height;
	}

	void DebugRect::Draw()
	{
		SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.g, m_colour.a);
		SDL_RenderFillRect(m_renderer, &m_rect);
	}

	DebugLine::DebugLine(const DebugLineInfo& info)
		: m_start_x_pos(info.start_x_pos)
		, m_start_y_pos(info.start_y_pos)
		, m_end_x_pos(info.end_x_pos)
		, m_end_y_pos(info.end_y_pos)
		, m_colour(info.colour)
		, m_renderer(info.renderer)
	{
	}

	void DebugLine::Draw()
	{
		SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.g, m_colour.a);
		SDL_RenderDrawLine(m_renderer, m_start_x_pos, m_start_y_pos, m_end_x_pos, m_end_y_pos);
	}

	DebugPoint::DebugPoint(const DebugPointInfo& info)
		: m_x_pos(info.x_pos)
		, m_y_pos(info.y_pos)
		, m_colour(info.colour)
		, m_renderer(info.renderer)
	{
	}

	void DebugPoint::Draw()
	{
		SDL_SetRenderDrawColor(m_renderer, m_colour.r, m_colour.g, m_colour.g, m_colour.a);
		SDL_RenderDrawPoint(m_renderer, m_x_pos, m_y_pos);
	}
}