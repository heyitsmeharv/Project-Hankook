#pragma once

#include <vector>
#include <SDL_events.h>

#include "imgui/imgui.h"
#include "Window.h"

namespace hk
{
	class ImGuiManager
	{
	public:
		 ImGuiManager(const hk::WindowInitData& init_data);
		~ImGuiManager();

		void Create		();
		void Destroy	();

		void Update		(SDL_Event& event);
		void StartFrame	();
		void Draw		();

	private:
		hk::Window m_window;
	};
}