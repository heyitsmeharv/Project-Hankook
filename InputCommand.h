#pragma once

#include <memory>

namespace hk
{
	class GameObject;
	class Camera;

	class InputCommand
	{
	public:
		virtual ~InputCommand() {}

		virtual std::unique_ptr<InputCommand>	Clone	() const = 0;
		virtual void							Execute	(GameObject&, Camera*) const = 0;
	};
}