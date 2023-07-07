#pragma once

#include <memory>

namespace hk
{
	class Command
	{
	public:
		virtual ~Command() {}

		virtual std::unique_ptr<Command>	Clone	() const = 0;
		virtual void						Execute	() const = 0;
	};
}