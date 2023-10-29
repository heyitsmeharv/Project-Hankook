#include "ChangeCameraZoomInputCommand.h"
#include "ChangeCameraZoomModelCommand.h"
#include "Logger.h"
#include "GameModelAccess.h"
#include "GameModel.h"

namespace hk
{
	ChangeCameraZoomInputCommand::ChangeCameraZoomInputCommand(const float delta)
		: m_delta(delta)
	{
	}

	ChangeCameraZoomInputCommand::~ChangeCameraZoomInputCommand()
	{
	}

	std::unique_ptr<InputCommand> ChangeCameraZoomInputCommand::Clone() const
	{
		return std::make_unique<ChangeCameraZoomInputCommand>(*this);
	}

	void ChangeCameraZoomInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo&)
	{
	}

	void ChangeCameraZoomInputCommand::Execute(GameObject&, Camera* camera) const
	{
		if (camera)
		{
			hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "ChangeCameraZoomInputCommand Executed with %f", m_delta);
			GetGameModel().QueueModelCommand(std::make_unique<ChangeCameraZoomModelCommand>(*camera, m_delta));
		}
	}
}