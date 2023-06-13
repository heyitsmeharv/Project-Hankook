#include "ImGuiManager.h"

#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

namespace hk
{
	ImGuiManager::ImGuiManager(const hk::WindowInitData& init_data)
		: m_window(init_data)
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

		m_window.Destroy();
	}

	void ImGuiManager::Update(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	void ImGuiManager::StartFrame()
	{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiManager::Draw()
	{
		//static bool show_demo_window = false;
		//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();

		ImGuiIO& io = ImGui::GetIO();
		SDL_RenderSetScale(m_window.GetRenderer(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);

		m_window.Clear();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		m_window.Display();
	}
}