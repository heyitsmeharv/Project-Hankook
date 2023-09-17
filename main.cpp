#include <SDL.h>
#include <SDL_image.h>

#include "Engine.h"
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
// - Create a basic tamagotchi or something like that
// - Create a basic puzzle game? 
// - Have proper command pipeline execution (not sporadic around codebase)
// - Collisions
// - Database loading
// - Level loading
// - Animated Sprite 
// - Movement
// - Clean includes
// - Will probably need a proper Event Pipeline


// - Add a character that's controlled X
// - Add item in level X
// - Allow for interaction with item
// - On interaction, load a 2D puzzle
// - Have pet follow character
// - Create button on UI
// - On button press, show Pet info


// - Make collision system class
// - Create variant for each collision type (monostate, circle, AABB, OBB, poly)
// - Add (De)Register functions to the system
// - Add a collision check function that is called whenever a game object moves
// - If function returns true, move the game object back

int main(int argc, char* args[])
{
	argc; args;

	srand(time(NULL));

	//hk::TamagotchiModel model;
	//model.Initialise();

	//hk::CollisionObject circle_a = hk::Circle{ { 0.0f, 0.0f }, 5.0f };
	//hk::CollisionObject circle_b = hk::Circle{ { 2.5f, 2.5f }, 5.0f };
	//hk::CollisionObject circle_c = hk::Circle{ { 2.5f, 25.5f }, 5.0f };
	//
	//hk::CollisionObject aabb_a = hk::AABB{ { 0.0f, 0.0f }, { 10.0f, 2.5f } };
	//hk::CollisionObject aabb_b = hk::AABB{ { 10.0f, 0.0f }, { 10.0f, 2.5f } };
	//
	//hk::CollisionSystem collision_system;
	//collision_system.RegisterCollisionObject(&circle_a);
	//collision_system.RegisterCollisionObject(&circle_b);
	//collision_system.RegisterCollisionObject(&aabb_a);
	//collision_system.RegisterCollisionObject(&aabb_b);
	//
	//const bool result = collision_system.AreObjectsColliding(circle_a, circle_c);

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