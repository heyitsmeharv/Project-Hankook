#pragma once

#include "ControllerInstance.h"
#include "GamepadMapping.h"

namespace hk
{
	class GamepadDevice;

	class GamepadInstance final : public ControllerInstance
	{
	public:
		 GamepadInstance(const GamepadDevice* device);
		~GamepadInstance();

		std::vector<std::unique_ptr<InputCommand>> Update() const override;

		void AttachDevice(const GamepadDevice& device);

	private:
		const GamepadDevice*	m_device;
		GamepadMapping			m_mapping;
	};
}