#pragma once

#include "Command.h"

namespace hk
{
	class MoveCommand : public Command
	{
	public:
		  MoveCommand(const int x_delta, const int y_delta);
		 ~MoveCommand();

		std::unique_ptr<Command> Clone() const override;
		void Execute(GameObject& game_object) const override;

	private:
		int m_x_delta;
		int m_y_delta;

	};
}