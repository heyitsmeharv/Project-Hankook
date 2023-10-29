#pragma once

#include "InputCommand.h"

namespace hk
{
	class InteractInputCommand : public InputCommand
	{
	public:
		std::unique_ptr<InputCommand>	Clone					 () const override;
		void							ConfigureFromDeviceInput (const DeviceInputInfo&) override;
		void							Execute					 (GameObject& game_object, Camera*) const override;
	};
}