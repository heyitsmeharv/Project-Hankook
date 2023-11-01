#pragma once

#include "ControllerInstance.h"
#include "KeyboardMouseMapping.h"

namespace hk
{
	class KeyboardMouseDevice;

	class KeyboardMouseInstance final : public ControllerInstance
	{
	public:
		 KeyboardMouseInstance(const KeyboardMouseDevice* device);
		~KeyboardMouseInstance();

		std::vector<std::unique_ptr<InputCommand>> Update() const override;

		void AttachDevice(const KeyboardMouseDevice& device);

	private:
		std::unique_ptr<InputCommand> GetCommandFromBinding(const InputCommandBinding& binding) const;

	private:
		const KeyboardMouseDevice*	m_device;
		KeyboardMouseMapping		m_mapping;
	};
}