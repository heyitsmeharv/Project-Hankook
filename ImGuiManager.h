#pragma once

#include <vector>
#include <SDL_events.h>

#include "Window.h"

namespace hk
{
	class ImGuiUser;

	class ImGuiManager
	{
	public:
		 ImGuiManager(const hk::WindowInitData& init_data);
		~ImGuiManager();

		void Create			();
		void Destroy		();

		void UpdateInput	(SDL_Event& event);
		void StartFrame		();
		void CallUsers		();
		void Draw			();

		static void RegisterUser	(ImGuiUser& user);
		static void DeregisterUser	(ImGuiUser& user);

	private:
		hk::Window m_window;

		static inline std::vector<ImGuiUser*> m_users;
	};
}