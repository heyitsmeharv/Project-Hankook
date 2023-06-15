#include <SDL.h> 
#include <iostream>  

#include "DebugShape.h"
#include "ErrorManager.h"
#include "ImGuiManager.h"
#include "KeyboardInputHandler.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "TextureManager.h"
#include "Timer.h"
#include "Window.h"

//*********************
//***** TODO LIST *****
//*********************
// - TextureManager
// - ErrorHandler
// - Animated Sprite
// - Movement
// - Collision
// - Clean includes

int main(int argc, char* args[])
{
	argc; args;

	hk::ErrorManager::Error(hk::ErrorCategory::GFX, "Test error: %s %d %f", "ww2n", 100, 30.2f);
	hk::ErrorManager::Error(hk::ErrorCategory::GFX, "Test error: %s %d %f", "ww2n", 100, 30.2f);
	hk::ErrorManager::Error(hk::ErrorCategory::GFX, "Test error: %s %d %f", "ww2n", 101, 30.2f);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		hk::ErrorManager::Error(hk::ErrorCategory::GFX, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//----- WINDOW -----
		hk::WindowInitData init_data;
		init_data.window_title = "Project Hankook";
		init_data.width = 800;
		init_data.height = 800;
		init_data.x_pos = 800;
		init_data.y_pos = 200;
		init_data.flags = SDL_WINDOW_SHOWN;

		hk::Window window{ init_data };

		//----- IMGUI -----
		hk::WindowInitData imgui_init_data;
		imgui_init_data.window_title = "Project Hankook - ImGui Debug";
		imgui_init_data.width = 600;
		imgui_init_data.height = 800;
		imgui_init_data.x_pos = 100;
		imgui_init_data.y_pos = 200;
		imgui_init_data.flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN;

		hk::ImGuiManager imgui_manager{ imgui_init_data };

		//----- TEXTURES -----
		if (hk::TextureManager::Instance().Initialise(window.GetRenderer(), "Data/Images/default.jpg") == false)
		{
			hk::ErrorManager::Error(hk::ErrorCategory::GFX, "TextureManager failed to load, we're in big trouble!");
			return -1;
		}

		hk::TextureManager::Instance().LoadDirectory("Data/Images");

		//----- TEXTURE -----
		hk::TextureInitInfo texture_info;
		texture_info.filepath = "Data/Images/kenny.jpg";
		texture_info.renderer = window.GetRenderer();

		hk::TextureManager::Instance().LoadTexture(texture_info);

		//----- INPUT HANDLER -----
		hk::KeyboardInputHandler input_handler;

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

		//----- Sprite -----
		hk::Sprite sprite{ "Data/Images/kenny.jpg" };
		sprite.SetPosition(200, 200);

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
				imgui_manager.Update(e);

				switch (e.type) 
				{
					case SDL_KEYDOWN:
					{
						input_handler.Update(e);
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

			debug_rect.Draw();
			debug_line.Draw();
			sprite_anim.Draw();
			sprite.Draw();

			window.Display();

			//----- IMGUI -----
			imgui_manager.StartFrame();
			sprite_anim.AddToImGui();
			timer.AddToImGui();
			hk::ErrorManager::AddToImGui();
			imgui_manager.Draw();
		}

		//Technically not necessary as is called in dtor
		imgui_manager.Destroy();
		window.Destroy();
	}

	SDL_Quit();
	
	return 0; 
}