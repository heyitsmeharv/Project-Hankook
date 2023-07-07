#pragma once

#include "ControllerInstance.h"
#include "GamepadMapping.h"

namespace hk
{
	class GamepadDevice;

	class GamepadInstance final : public ControllerInstance
	{
	public:
		 GamepadInstance();
		~GamepadInstance();

		std::vector<std::unique_ptr<Command>> HandleInput() const override;

		void AttachDevice(const GamepadDevice& device);

	private:
		const GamepadDevice*	m_device;
		GamepadMapping			m_mapping;
	};
}