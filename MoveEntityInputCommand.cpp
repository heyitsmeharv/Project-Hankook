#include "MoveEntityInputCommand.h"
#include "MoveEntityModelCommand.h"

#include "Logger.h"
#include "GameModelAccess.h"
#include "GameModel.h"

namespace hk
{
	MoveEntityInputCommand::MoveEntityInputCommand(const float x_delta, const float y_delta)
		: m_x_delta(x_delta)
		, m_y_delta(y_delta)
	{
	}

	MoveEntityInputCommand::~MoveEntityInputCommand()
	{
	}

	std::unique_ptr<InputCommand> MoveEntityInputCommand::Clone() const
	{
		return std::make_unique<MoveEntityInputCommand>(*this);
	}

	void MoveEntityInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo& info)
	{
		m_x_delta *= info.press_modifier;
		m_y_delta *= info.press_modifier;
	}

	void MoveEntityInputCommand::Execute(entt::entity controlled_entity, entt::entity) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveEntityInputCommand executed on entity %d with x: %f, y: %f", controlled_entity, m_x_delta, m_y_delta);
		GetGameModel().QueueModelCommand(std::make_unique<MoveEntityModelCommand>(controlled_entity, Vector2f{ m_x_delta, m_y_delta }));
	}
}