#pragma once

#include <memory>
#include <vector>

namespace hk
{
	class InputCommand;

	class ControllerInstance
	{
	public:
		virtual ~ControllerInstance();

		virtual std::vector<std::unique_ptr<InputCommand>> Update() const = 0;
	};
}