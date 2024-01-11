#include "ZoomCameraInputCommand.h"
#include "ZoomCameraModelCommand.h"

#include "Logger.h"
#include "GameModel.h"

namespace hk
{
	ZoomCameraInputCommand::ZoomCameraInputCommand(const float delta)
		: m_delta(delta)
	{
	}

	ZoomCameraInputCommand::~ZoomCameraInputCommand()
	{
	}

	std::unique_ptr<InputCommand> ZoomCameraInputCommand::Clone() const
	{
		return std::make_unique<ZoomCameraInputCommand>(*this);
	}

	void ZoomCameraInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo&)
	{
	}

	void ZoomCameraInputCommand::Execute(entt::entity, entt::entity camera_entity, GameModel& model) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "ZoomCameraModelCommand executed on entity %d with %f", camera_entity, m_delta);
		model.QueueModelCommand(std::make_unique<ZoomCameraModelCommand>(camera_entity, m_delta));
	}
}