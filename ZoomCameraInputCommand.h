#pragma once

#include "InputCommand.h"

namespace hk
{
	class ZoomCameraInputCommand : public InputCommand
	{
	public:
		 ZoomCameraInputCommand(const float delta);
		~ZoomCameraInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;

		void ConfigureFromDeviceInput	(const DeviceInputInfo& info) override;
		void Execute					(entt::entity controlled_entity, entt::entity camera_entity, GameModel& model) const override;

	private:
		float m_delta;
	};
}