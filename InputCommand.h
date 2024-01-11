#pragma once

#include <entt/fwd.hpp>
#include <memory>

namespace hk
{
	class GameModel;

	struct DeviceInputInfo
	{
		// Mainly for joysticks but allows hardware sensitivity to be known
		float press_modifier = 1.0f;
	};

	class InputCommand
	{
	public:
		virtual ~InputCommand() {}

		virtual std::unique_ptr<InputCommand>	Clone					() const = 0;
		virtual void							ConfigureFromDeviceInput(const DeviceInputInfo&) = 0;
		virtual void							Execute					(entt::entity controlled_entity, entt::entity camera_entity, GameModel& model) const = 0;
	};
}