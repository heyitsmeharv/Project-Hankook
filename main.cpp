#include <SDL.h> 
#include <iostream>  

#include "DebugShape.h"
#include "ErrorManager.h"
#include "GameObject.h"
#include "GamepadInstance.h"
#include "ImGuiManager.h"
#include "InputDeviceManager.h"
#include "KeyboardMouseInstance.h"
#include "Logger.h"
#include "PlayerController.h"
#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Vector2.h"
#include "Window.h"

//*********************
//***** TODO LIST *****
//*********************
// - TextureManager X
// - ErrorHandler X
// - ImGui User class X
// - Game Object Class (diff between sprite, drawable and game object) X
// - Rework Input Handling X
// - Logger (Inputs, Commands etc) X
// - Sprite move with controllers (i.e. keyboard-mouse + ps5)
// - Spawn more GameObjects on button press (i.e. a gun shooting bullets)
// - Have proper command pipeline execution (not sporadic around codebase)
// - Collisions
// - Database loading
// - Level loading
// - Animated Sprite 
// - Movement
// - Clean includes
// - Will probably need a proper Event Pipeline

int main(int argc, char* args[])
{
	argc; args;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) < 0)
	{
		hk::Fatal(hk::ErrorCategory::GFX, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//----- WINDOW -----
		hk::WindowInitData init_data;
		init_data.window_title = "Project Hankook";
		init_data.width = 800;
		init_data.height = 800;
		init_data.x_pos = 1000;
		init_data.y_pos = 200;
		init_data.flags = SDL_WINDOW_SHOWN;

		hk::Window window{ init_data };

		//----- IMGUI -----
		hk::WindowInitData imgui_init_data;
		imgui_init_data.window_title = "Project Hankook - ImGui Debug";
		imgui_init_data.width = 800;
		imgui_init_data.height = 600;
		imgui_init_data.x_pos = 100;
		imgui_init_data.y_pos = 200;
		imgui_init_data.flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN;

		hk::ImGuiManager imgui_manager{ imgui_init_data };

		//----- TEXTURES -----
		if (hk::TextureManager::Instance().Initialise(window.GetRenderer(), "Data/Images/default.jpg") == false)
		{
			hk::Fatal(hk::ErrorCategory::GFX, "TextureManager failed to load, we're in big trouble!");
			return -1;
		}

		hk::TextureManager::Instance().LoadDirectory("Data/Images");

		//----- TEXTURE -----
		hk::TextureInitInfo texture_info;
		texture_info.filepath = "Data/Images/kenny.jpg";
		texture_info.renderer = window.GetRenderer();

		hk::TextureManager::Instance().LoadTexture(texture_info);

		//----- INPUT -----
		hk::InputDeviceManager input_device_manager;
		input_device_manager.LoadKeyboardMouse();
		input_device_manager.LoadGamepads();
		
		hk::PlayerController player_controller;

		if (input_device_manager.GetGamepadDevices().empty() == false)
		{
			std::unique_ptr<hk::GamepadInstance> gamepad_instance = std::make_unique<hk::GamepadInstance>();
			gamepad_instance->AttachDevice(input_device_manager.GetGamepadDevices().front());

			player_controller.AttachControllerInstance(std::move(gamepad_instance));
		}
		else
		{
			std::unique_ptr<hk::KeyboardMouseInstance> keyboard_instance = std::make_unique<hk::KeyboardMouseInstance>();
			keyboard_instance->AttachDevice(input_device_manager.GetDefaultKeyboardMouse());

			player_controller.AttachControllerInstance(std::move(keyboard_instance));
		}

		//----- TIMER -----
		hk::Timer timer;

		//----- DEBUG SHAPES -----
		hk::DebugRectInfo rect_info;
		rect_info.x_pos = 300;
		rect_info.y_pos = 300;
		rect_info.width = 200;
		rect_info.height = 200;
		rect_info.renderer = window.GetRenderer();
		rect_info.colour = { 255, 0, 0, 255 };

		hk::DebugRect debug_rect{ rect_info };

		hk::DebugLineInfo line_info;
		line_info.start_x_pos = 0;
		line_info.start_y_pos = 0;
		line_info.end_x_pos = 800;
		line_info.end_y_pos = 800;
		line_info.renderer = window.GetRenderer();
		line_info.colour = { 255, 0, 0, 255 };

		hk::DebugLine debug_line{ line_info };

		//----- SPRITE ANIMATION -----
		hk::SpriteSheet sprite_sheet;
		sprite_sheet.Load("Data/Sprites/test_sprite_sheet.png");

		hk::SpriteAnimation sprite_anim;
		sprite_anim.SetSpriteSheet(&sprite_sheet);

		//----- GAME OBJECTS -----
		hk::GameObject root_object{ "root", { 400, 200 }, { 100, 100 }, nullptr };
		root_object.AddChild(std::make_unique<hk::GameObject>( "child", hk::Vector2i{400, 200}, hk::Vector2i{ 100, 100 }, &hk::TextureManager::Instance().GetTexture("Data/Images/kenny.jpg")));
		player_controller.AttachGameObject(root_object);

		//----- SINGLETONS -----
		hk::ErrorManager::Instance();
		hk::Logger::Instance();

		//----- MAIN LOOP -----
		timer.Restart();

		//Hack to get window to stay up
		bool quit = false; 
		while (quit == false) 
		{
			timer.Update();

			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				imgui_manager.UpdateInput(e);

				switch (e.type) 
				{
					case SDL_KEYUP:
					{
						hk::Logger::Instance().AddEntry(hk::LogCategory::INPUT, "Key Released: %s", SDL_GetScancodeName(e.key.keysym.scancode));
						player_controller.OnInputChange();
						break;
					}
					case SDL_KEYDOWN:
					{
						hk::Logger::Instance().AddEntry(hk::LogCategory::INPUT, "Key Pressed: %s", SDL_GetScancodeName(e.key.keysym.scancode));
						player_controller.OnInputChange();
						break;
					}
					case SDL_JOYBUTTONDOWN:
					{
						hk::Logger::Instance().AddEntry(hk::LogCategory::INPUT, "Joystick %d Pressed: %d", static_cast<int>(e.jbutton.which), static_cast<int>(e.jbutton.button));
						player_controller.OnInputChange();
						break;
					}
					case SDL_JOYAXISMOTION:
                    {
						//Purposely no log here otherwise the log would get spammed with millions of micro-movements
						player_controller.OnInputChange();
						break;
					}
					case SDL_CONTROLLERDEVICEADDED:
					case SDL_CONTROLLERDEVICEREMOVED:
					{
						//Add device addition/removal here when we get the chance
						break;
					}
					//SDL_QUIT doesn't play nicely with more than one window...
					case SDL_WINDOWEVENT:
					{
						//If the event was hitting the close button and it was from the main game window, then quit
						if (e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window.GetWindow()))
						{
							quit = true;
						}
						break;
					}
					default:
					{
						break;
					}
				}
			}

			sprite_anim.Update();

			window.Clear();

			//debug_rect.Draw();
			//debug_line.Draw();
			//sprite_anim.Draw();
			root_object.Draw();

			window.Display();

			//----- IMGUI -----
			imgui_manager.StartFrame();
			imgui_manager.CallUsers();

			// GameObject is a special case atm as we don't want to call every GameObject
			// We let the hierarchy handle that
			if (ImGui::Begin("Game Objects"))
			{
				root_object.AddToImGui();
				ImGui::End();
			}

			imgui_manager.Draw();
		}

		//Technically not necessary as is called in dtor
		imgui_manager.Destroy();
		window.Destroy();
	}

	SDL_Quit();
	
	return 0; 
}