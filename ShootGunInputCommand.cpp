#include <stdlib.h>

#include "ShootGunInputCommand.h"
#include "Logger.h"
#include "Engine.h"
#include "EngineAccess.h"
#include "ProjectileGameObject.h"
#include "TextureManager.h"

namespace hk
{
	ShootGunInputCommand::ShootGunInputCommand()
	{
	}

	ShootGunInputCommand::~ShootGunInputCommand()
	{
	}

	std::unique_ptr<InputCommand> ShootGunInputCommand::Clone() const
	{
		return std::make_unique<ShootGunInputCommand>(*this);
	}

	void ShootGunInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo&)
	{
	}

	void ShootGunInputCommand::Execute(GameObject& game_object, Camera*) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "ShootGunCommand Executed");

		static uint32_t id_num = 0;
		std::string id = "bullet" + std::to_string(id_num++);

		const int x_dir = (rand() % 100) - 50;
		const int y_dir = (rand() % 100) - 50;

		ProjectileGameObjectInitInfo init_info;
		init_info.id = id;
		init_info.position = game_object.GetPosition();
		init_info.dimensions = { 8, 8 };
		init_info.texture = &GetEngine().GetTextureManager().GetTexture("Data\\Images\\blank_circle_64.png");
		init_info.colour_mod = SDL_Color{};
		init_info.colour_mod->r = 255;
		init_info.colour_mod->a = 255;
		init_info.direction = { (float)x_dir, (float)y_dir };
		init_info.velocity = 1.0;
		init_info.lifetime = 3.0;

		GameObject::RootObject()->AddChild(std::make_unique<ProjectileGameObject>(init_info));
	}
}