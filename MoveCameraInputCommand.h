#pragma once

#include "InputCommand.h"

namespace hk
{
	class MoveCameraInputCommand : public InputCommand
	{
	public:
		MoveCameraInputCommand(const float x_delta, const float y_delta);
		~MoveCameraInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;

		void ConfigureFromDeviceInput(const DeviceInputInfo& info) override;
		void Execute(GameObject& game_object, Camera*) const override;

	private:
		float m_x_delta;
		float m_y_delta;
	};
}