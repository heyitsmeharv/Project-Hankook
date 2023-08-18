#pragma once

#include "InputCommand.h"

namespace hk
{
	class MoveObjectInputCommand : public InputCommand
	{
	public:
		MoveObjectInputCommand(const float x_delta, const float y_delta);
		 ~MoveObjectInputCommand();

		std::unique_ptr<InputCommand> Clone() const override;
		void Execute(GameObject& game_object, Camera*) const override;

	private:
		float m_x_delta;
		float m_y_delta;

	};
}