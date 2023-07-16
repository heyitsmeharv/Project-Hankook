#pragma once

#include "Command.h"

namespace hk
{
	class ShootGunCommand : public Command
	{
	public:
		ShootGunCommand();
		~ShootGunCommand();

		std::unique_ptr<Command> Clone() const override;
		void Execute(GameObject& game_object) const override;

	};
}