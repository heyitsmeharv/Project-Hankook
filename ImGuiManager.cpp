#include "ImGuiManager.h"
#include "ImGuiUser.h"

#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

#include "Window.h"

namespace hk
{
	ImGuiManager::ImGuiManager(hk::Window& window)
		: m_window(window)
	{
		Create();
	}

	ImGuiManager::~ImGuiManager()
	{
		Destroy();
	}

	void ImGuiManager::Create()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(m_window.GetWindow(), m_window.GetRenderer());
		ImGui_ImplSDLRenderer2_Init(m_window.GetRenderer());
	}

	void ImGuiManager::Destroy()
	{
		if (ImGui::GetCurrentContext() != nullptr)
		{
			ImGui_ImplSDLRenderer2_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}
	}

	void ImGuiManager::UpdateInput(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	void ImGuiManager::StartFrame()
	{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiManager::EndFrame()
	{
		ImGui::EndFrame();
	}

	void ImGuiManager::CallUsers()
	{
		for (auto& user : m_users)
		{
			if (user)
			{
				user->AddToImGui();
			}
		}
	}

	void ImGuiManager::Draw()
	{
		//static bool show_demo_window = false;
		//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();

		ImGuiIO& io = ImGui::GetIO();
		SDL_RenderSetScale(m_window.GetRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiManager::RegisterUser(ImGuiUser& user)
	{
		m_users.push_back(&user);
	}

	void ImGuiManager::DeregisterUser(ImGuiUser& user)
	{
		auto itr = std::find(m_users.begin(), m_users.end(), &user);
		if (itr != m_users.end())
		{
			m_users.erase(itr);
		}
	}
}