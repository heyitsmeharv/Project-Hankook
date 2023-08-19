#pragma once

#include "InputCommand.h"

namespace hk
{
	class ShootGunInputCommand : public InputCommand
	{
	public:
		ShootGunInputCommand();
		~ShootGunInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;

		void ConfigureFromDeviceInput(const DeviceInputInfo& info) override;
		void Execute(GameObject& game_object, Camera*) const override;

	};
}