#pragma once

#include "ControllerInstance.h"
#include "KeyboardMouseMapping.h"

namespace hk
{
	class KeyboardMouseDevice;

	class KeyboardMouseInstance final : public ControllerInstance
	{
	public:
		 KeyboardMouseInstance();
		~KeyboardMouseInstance();

		std::vector<std::unique_ptr<Command>> HandleInput() const override;

		void AttachDevice(const KeyboardMouseDevice& device);

	private:
		const KeyboardMouseDevice*	m_device;
		KeyboardMouseMapping		m_mapping;
	};
}