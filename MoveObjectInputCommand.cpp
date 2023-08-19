#include "MoveObjectInputCommand.h"
#include "Logger.h"

#include "GameObject.h"

namespace hk
{
	MoveObjectInputCommand::MoveObjectInputCommand(const float x_delta, const float y_delta)
		: m_x_delta(x_delta)
		, m_y_delta(y_delta)
	{		
	}

	MoveObjectInputCommand::~MoveObjectInputCommand()
	{
	}

	std::unique_ptr<InputCommand> MoveObjectInputCommand::Clone() const
	{
		return std::make_unique<MoveObjectInputCommand>(*this);
	}

	void MoveObjectInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo& info)
	{
		m_x_delta *= info.press_modifier;
		m_y_delta *= info.press_modifier;
	}

	void MoveObjectInputCommand::Execute(GameObject& game_object, Camera*) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveObjectInputCommand Executed with x: %f, y: %f", m_x_delta, m_y_delta);
		game_object.MovePosition(m_x_delta, m_y_delta);
	}
}