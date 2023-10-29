#include "InteractInputCommand.h"
#include "Logger.h"
#include "GameModel.h"
#include "GameModelAccess.h"
#include "InteractModelCommand.h"

namespace hk
{
	std::unique_ptr<InputCommand> InteractInputCommand::Clone() const
	{
		return std::make_unique<InteractInputCommand>(*this);
	}

	void InteractInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo&)
	{
	}

	void InteractInputCommand::Execute(GameObject& game_object, Camera*) const
	{
		hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "InteractInputCommand Executed");
		GetGameModel().QueueModelCommand(std::make_unique<InteractModelCommand>(game_object));
	}
}