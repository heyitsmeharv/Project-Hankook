#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine.h"
#include "EngineAccess.h"
#include "Timer.h"

//*********************
//***** TODO LIST *****
//*********************
// - TextureManager X
// - ErrorHandler X
// - ImGui User class X
// - Game Object Class (diff between sprite, drawable and game object) X
// - Rework Input Handling X
// - Logger (Inputs, Commands etc) X
// - Sprite move with controllers (i.e. keyboard-mouse + ps5) X
// - Spawn more GameObjects on button press (i.e. a gun shooting bullets) X
// - Create a model class for game logic execution
// - EnTT rewrite X
// - Load object layer from Tiled
// - Spawn a controller player
// - Think about collision system

int main(int argc, char* args[])
{
	argc; args;

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) < 0)
	{
		hk::Fatal(hk::ErrorCategory::GFX, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		hk::Fatal(hk::ErrorCategory::GFX, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return -1;
	}

	hk::Engine engine;
	hk::RegisterEngine(engine);

	engine.Start();

	//----- TIMER -----
	hk::Timer timer;

	//----- MAIN LOOP -----
	timer.Restart();

	while (engine.IsShutdownRequested() == false)
	{
		timer.Update();

		engine.Update(timer.DeltaTime());
		engine.Draw();
	}
	
	engine.Shutdown();

	IMG_Quit();
	SDL_Quit();
	
	return 0; 
}