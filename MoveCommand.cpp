#include "MoveCommand.h"
#include "Logger.h"

#include "GameObject.h"

namespace hk
{
	MoveCommand::MoveCommand(const int x_delta, const int y_delta)
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

	void MoveCommand::Execute(GameObject& game_object) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveCommand Executed with x: %f, y: %f", m_x_delta, m_y_delta);

		game_object.MovePosition(m_x_delta, m_y_delta);
	}
}