#include "Timer.h"

#include "imgui/imgui.h"

namespace
{
	std::chrono::high_resolution_clock::time_point CurrentTick()
	{
		return std::chrono::high_resolution_clock::now();
	}
}

namespace hk
{
	Timer::Timer()
		: m_delta_time()
		, m_total_time()
		, m_last_tick()
	{
	}

	void Timer::Restart()
	{
		m_delta_time = std::chrono::seconds{ 0 };
		m_last_tick = CurrentTick();
	}

	void Timer::Update()
	{
		if (m_is_paused == false)
		{
			std::chrono::high_resolution_clock::time_point current_tick = CurrentTick();

			m_delta_time = duration_cast<std::chrono::duration<double>>(current_tick - m_last_tick);
			m_last_tick = current_tick;
		}
		
		m_total_time += m_delta_time;
	}

	void Timer::Pause()
	{
		if (m_is_paused == false)
		{
			m_is_paused = true;
			m_delta_time = std::chrono::duration<double>{ 0.0 };
		}
	}

	void Timer::Resume()
	{
		if (m_is_paused)
		{
			m_is_paused = false;
			m_last_tick = CurrentTick();
		}
	}

	double Timer::DeltaTime() const
	{
		return m_delta_time.count();
	}

	double Timer::TotalTime() const
	{
		return m_total_time.count();
	}

	void Timer::AddToImGui()
	{
		ImGui::Begin("Timer");

		//Seems a tad silly but directly accessing m_is_paused isn't enough
		//We need to call the functions for extra logic
		static bool is_paused = m_is_paused;
		if (ImGui::Checkbox("Is Paused", &is_paused))
		{
			if (is_paused)
			{
				Pause();
			}
			else
			{
				Resume();
			}
		}

		ImGui::Text("%lf - Delta Time", DeltaTime());
		ImGui::Text("%lf - Total Time", TotalTime());
		ImGui::End();
	}
}