#include "MoveCommand.h"
#include "Logger.h"

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

	std::unique_ptr<Command> MoveCommand::Clone() const
	{
		return std::make_unique<MoveCommand>(*this);
	}

	void MoveCommand::Execute() const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveCommand Executed with x: %f, y: %f", m_x_delta, m_y_delta);

		//transformable.move(m_x_delta, m_y_delta);
	}
}