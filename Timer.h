#pragma once

#include <chrono>

namespace hk
{
	class Timer
	{
	public:
		Timer();

		void	Restart		();
		void	Update		();
		void	Pause		();
		void	Resume		();

		double	DeltaTime	() const;
		double	TotalTime	() const;

		void	AddToImGui	();

	private:
		//This is stored as seconds so 0.016s
		std::chrono::duration<double>					m_delta_time;
		std::chrono::duration<double>					m_total_time;
		std::chrono::high_resolution_clock::time_point	m_last_tick;

		bool m_is_paused = false;
	};
}