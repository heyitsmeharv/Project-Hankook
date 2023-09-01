#pragma once

#include <vector>
#include <SDL_events.h>

namespace hk
{
	class Window;

	class ImGuiUser;

	class ImGuiManager
	{
	public:
		 ImGuiManager(hk::Window& window);
		~ImGuiManager();

		void Create			();
		void Destroy		();

		void UpdateInput	(SDL_Event& event);
		void StartFrame		();
		void EndFrame		();
		void CallUsers		();
		void Draw			();

		static void RegisterUser	(ImGuiUser& user);
		static void DeregisterUser	(ImGuiUser& user);

	private:
		hk::Window& m_window;

		static inline std::vector<ImGuiUser*> m_users;
	};
}