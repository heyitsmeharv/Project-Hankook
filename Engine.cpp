#include "Engine.h"

#include "ErrorManager.h"
#include "GamepadInstance.h"
#include "ImGuiManager.h"
#include "KeyboardMouseInstance.h"
#include "WordSearchModel.h"

namespace hk
{
	Engine::Engine()
		: m_windows()
		, m_texture_manager()
		, m_input_device_manager()
		, m_game_model(std::make_unique<WordSearchModel>(*this))
		, m_is_shutdown_requested(false)
		, m_has_shutdown(false)

		, m_error_manager()
		, m_logger()
		, m_imgui_manager(nullptr)
	{
	}

	Engine::~Engine()
	{
		Shutdown();
	}

	bool Engine::Start()
	{
		LoadGameWindow();
		LoadImGui();
		LoadTextureManager();
		LoadTextures();
		LoadInputDeviceManager();

		m_game_model->Initialise();

		return true;
	}

	void Engine::Shutdown()
	{
		if (m_has_shutdown == false)
		{
			m_texture_manager.Destroy();

			if (m_imgui_manager)
			{
				m_imgui_manager->Destroy();
				m_imgui_manager.reset();
			}

			for (auto& window : m_windows)
			{
				window.Destroy();
			}

			m_has_shutdown = true;
		}
	}

	void Engine::Update(double delta_time)
	{
		if (m_is_shutdown_requested == false)
		{
			m_input_device_manager.NewTick();

			ProcessEvents();

			m_input_device_manager.Update(delta_time);
			m_game_model->Update(delta_time);
		}
	}

	void Engine::ProcessEvents()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			for (auto& window : m_windows)
			{
				window.ProcessEvent(e);
			}

			if (m_imgui_manager)
			{
				m_imgui_manager->ProcessEvent(e);
			}

			m_input_device_manager.ProcessEvent(e);

			switch (e.type)
			{
				//SDL_QUIT doesn't play nicely with more than one window...
				case SDL_WINDOWEVENT:
				{
					//If the event was hitting the close button and it was from the main game window, then quit
					if (e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(GameWindow().GetWindow()))
					{
						m_is_shutdown_requested = true;
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	void Engine::Draw()
	{
		for (auto& window : m_windows)
		{
			window.Clear();
		}

		if (m_imgui_manager)
		{
			m_imgui_manager->StartFrame();
			m_imgui_manager->CallUsers();
			m_imgui_manager->EndFrame();
			m_imgui_manager->Draw();
		}

		std::sort(m_draw_requests.begin(), m_draw_requests.end(), [](const auto& lhs, const auto& rhs) { return lhs->z_index < rhs->z_index; });

		for (const auto& request : m_draw_requests)
		{
			request->HandleRequest();
		}

		for (auto& window : m_windows)
		{
			window.Display();
		}

		m_draw_requests.clear();
	}

	void Engine::AddDrawRequest(std::unique_ptr<DrawRequest>&& draw_request)
	{
		m_draw_requests.push_back(std::move(draw_request));
	}

	Window& Engine::CreateWindow(const WindowInitInfo& window_info)
	{
		m_windows.emplace_back( window_info );
		return m_windows.back();
	}

	bool Engine::LoadGameWindow()
	{
		hk::WindowInitInfo window_init_info;
		window_init_info.window_title = "Project Hankook";
		window_init_info.width = 1200;
		window_init_info.height = 800;
		window_init_info.x_pos = 1000;
		window_init_info.y_pos = 200;
		window_init_info.flags = SDL_WINDOW_SHOWN;
		window_init_info.clear_colour = { 100, 100, 100, 255 };

		CreateWindow(window_init_info);

		return true;
	}

	bool Engine::LoadTextureManager()
	{
		if (m_texture_manager.Initialise(m_windows[0].GetRenderer(), "Data\\Images\\default.jpg") == false)
		{
			hk::Fatal(hk::ErrorCategory::GFX, "TextureManager failed to load, we're in big trouble!");
			return false;
		}

		return true;
	}

	bool Engine::LoadTextures()
	{
		m_texture_manager.LoadDirectory("Data\\Images");
		m_texture_manager.LoadDirectory("Data\\Tilemap");

		return true;
	}

	bool Engine::LoadInputDeviceManager()
	{
		m_input_device_manager.LoadKeyboardMouse();
		m_input_device_manager.LoadGamepads();

		return true;
	}

	bool Engine::LoadImGui()
	{
		hk::WindowInitInfo imgui_window_info;
		imgui_window_info.window_title = "Project Hankook - ImGui Debug";
		imgui_window_info.width = 800;
		imgui_window_info.height = 600;
		imgui_window_info.x_pos = 100;
		imgui_window_info.y_pos = 200;
		imgui_window_info.flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN;

		Window& imgui_window = CreateWindow(imgui_window_info);

		m_imgui_manager = std::make_unique<ImGuiManager>(imgui_window);

		return true;
	}

	bool Engine::IsShutdownRequested() const
	{
		return m_is_shutdown_requested;
	}

	Window& Engine::GameWindow()
	{
		return m_windows[0];
	}

	SDL_Renderer* Engine::Renderer()
	{
		return GameWindow().GetRenderer();
	}

	const TextureManager& Engine::GetTextureManager() const
	{
		return m_texture_manager;
	}

	const InputDeviceManager& Engine::GetInputDeviceManager() const
	{
		return m_input_device_manager;
	}
}