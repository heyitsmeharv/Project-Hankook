#include <stdlib.h>

#include "ShootGunCommand.h"
#include "Logger.h"

#include "ProjectileGameObject.h"
#include "TextureManager.h"

namespace hk
{
	ShootGunCommand::ShootGunCommand()
	{
	}

	ShootGunCommand::~ShootGunCommand()
	{
	}

	std::unique_ptr<Command> ShootGunCommand::Clone() const
	{
		return std::make_unique<ShootGunCommand>(*this);
	}

	void ShootGunCommand::Execute(GameObject& game_object) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "ShootGunCommand Executed");

		static uint32_t id_num = 0;
		std::string id = "bullet" + std::to_string(id_num++);

		const int x_dir = (rand() % 100) - 50;
		const int y_dir = (rand() % 100) - 50;

		ProjectileGameObjectInitInfo init_data;
		init_data.id = id;
		init_data.position = game_object.GetPosition();
		init_data.dimensions = { 8, 8 };
		init_data.texture = &hk::TextureManager::Instance().GetTexture("Data\\Images\\blank_circle_64.png");
		init_data.colour_mod = SDL_Color{};
		init_data.colour_mod->r = 255;
		init_data.colour_mod->a = 255;
		init_data.direction = { (float)x_dir, (float)y_dir };
		init_data.velocity = 1.0;
		init_data.lifetime = 3.0;

		GameObject::RootObject()->AddChild(std::make_unique<ProjectileGameObject>(init_data));
	}
}