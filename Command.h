#pragma once

#include <memory>

namespace hk
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() {}

		virtual std::unique_ptr<Command>	Clone	() const = 0;
		virtual void						Execute	(GameObject&) const = 0;
	};
}