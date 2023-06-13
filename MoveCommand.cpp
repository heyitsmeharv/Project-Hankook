#include "MoveCommand.h"

namespace hk
{
	MoveCommand::MoveCommand(/*Transformable& moveable,*/ const float x_delta, const float y_delta)
		: m_x_delta(x_delta)
		, m_y_delta(y_delta)
	{		
	}

	MoveCommand::~MoveCommand()
	{
	}

	void MoveCommand::Execute() const
	{
		//transformable.move(m_x_delta, m_y_delta);
	}
}