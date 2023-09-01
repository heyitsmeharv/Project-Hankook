#pragma once

#include <vector>

#include "CameraManager.h"
#include "DrawRequest.h"
#include "ErrorManager.h"
#include "GameModel.h"
#include "InputDeviceManager.h"
#include "Logger.h"
#include "PlayerController.h"
#include "TextureManager.h"
#include "Window.h"

namespace hk
{
	class ImGuiManager;

	class Engine
	{
	public:
		Engine();

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
		CameraManager&				GetCameraManager		();

	private:
		Window&						CreateWindow			(const WindowInitInfo& window_info);

		bool						LoadGameWindow			();
		bool						LoadTextureManager		();
		bool						LoadTextures			();
		bool						LoadInputDeviceManager	();
		bool						LoadCameraManager		();

		bool						LoadImGui				();

		void						UpdateInput				();

	private:
		std::vector<Window>							m_windows;
		std::vector<std::unique_ptr<DrawRequest>>	m_draw_requests;
		TextureManager								m_texture_manager;
		InputDeviceManager							m_input_device_manager;
		CameraManager								m_camera_manager;
		GameModel									m_game_model;
		bool										m_is_shutdown_requested;

		ErrorManager								m_error_manager;
		Logger										m_logger;
		std::unique_ptr<ImGuiManager>				m_imgui_manager;
	};
}