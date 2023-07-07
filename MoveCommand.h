#pragma once

#include "Command.h"

namespace hk
{
	class MoveCommand : public Command
	{
	public:
		  MoveCommand(/*Transformable& moveable,*/ const float x_delta, const float y_delta);
		 ~MoveCommand();

		std::unique_ptr<Command> Clone() const override;
		void Execute() const override;

	private:
		float m_x_delta;
		float m_y_delta;

	};
}