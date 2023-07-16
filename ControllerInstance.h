#pragma once

#include <memory>
#include <vector>

namespace hk
{
	class Command;

	class ControllerInstance
	{
	public:
		virtual ~ControllerInstance();

		virtual std::vector<std::unique_ptr<Command>> Update() const = 0;
	};
}