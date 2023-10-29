#pragma once

#include "InputCommand.h"

namespace hk
{
	class ChangeCameraZoomInputCommand : public InputCommand
	{
	public:
		ChangeCameraZoomInputCommand(const float delta);
		~ChangeCameraZoomInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;

		void ConfigureFromDeviceInput(const DeviceInputInfo& info) override;
		void Execute(GameObject& game_object, Camera*) const override;

	private:
		float m_delta;
	};
}