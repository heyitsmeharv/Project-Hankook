#pragma once

#include "InputCommand.h"

namespace hk
{
	class MoveEntityInputCommand : public InputCommand
	{
	public:
		 MoveEntityInputCommand(const float x_delta, const float y_delta);
		~MoveEntityInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;

		void ConfigureFromDeviceInput	(const DeviceInputInfo& info) override;
		void Execute					(entt::entity controlled_entity, entt::entity camera_entity, GameModel& model) const override;

	private:
		float m_x_delta;
		float m_y_delta;

	};
}