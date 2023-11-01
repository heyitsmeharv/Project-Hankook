#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "DrawRequest.h"
#include "ErrorManager.h"
#include "GameModel.h"
#include "InputDeviceManager.h"
#include "Logger.h"
#include "TextureManager.h"
#include "Window.h"

namespace hk
{
	class ImGuiManager;

	class Engine
	{
	public:
		 Engine();
		~Engine();

		bool						Start					();
		void						Shutdown				();
		bool						IsShutdownRequested		() const;

		void						Update					(double delta_time);
		void						Draw					();
		void						AddDrawRequest			(std::unique_ptr<DrawRequest>&& draw_request);

		Window&						GameWindow				();
		SDL_Renderer*				Renderer				();

		const InputDeviceManager&	GetInputDeviceManager	() const;
		const TextureManager&		GetTextureManager		() const;
		GameModel&					GetGameModel			();
		CollisionSystem&			GetCollisionSystem		();

	private:
		Window&						CreateWindow			(const WindowInitInfo& window_info);

		bool						LoadGameWindow			();
		bool						LoadTextureManager		();
		bool						LoadTextures			();
		bool						LoadInputDeviceManager	();

		bool						LoadImGui				();

		void						ProcessEvents			();

	private:
		std::vector<Window>							m_windows;
		std::vector<std::unique_ptr<DrawRequest>>	m_draw_requests;
		TextureManager								m_texture_manager;
		InputDeviceManager							m_input_device_manager;
		GameModel									m_game_model;
		CollisionSystem								m_collision_system;

		bool										m_is_shutdown_requested;
		bool										m_has_shutdown;

		ErrorManager								m_error_manager;
		Logger										m_logger;
		std::unique_ptr<ImGuiManager>				m_imgui_manager;
	};
}