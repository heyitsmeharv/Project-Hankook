#include "MoveCameraInputCommand.h"
#include "MoveCameraModelCommand.h"
#include "Logger.h"
#include "GameModelAccess.h"
#include "GameModel.h"

namespace hk
{
	MoveCameraInputCommand::MoveCameraInputCommand(const float x_delta, const float y_delta)
		: m_x_delta(x_delta)
		, m_y_delta(y_delta)
	{
	}

	MoveCameraInputCommand::~MoveCameraInputCommand()
	{
	}

	std::unique_ptr<InputCommand> MoveCameraInputCommand::Clone() const
	{
		return std::make_unique<MoveCameraInputCommand>(*this);
	}

	void MoveCameraInputCommand::ConfigureFromDeviceInput(const DeviceInputInfo& info)
	{
		m_x_delta *= info.press_modifier;
		m_y_delta *= info.press_modifier;
	}

	void MoveCameraInputCommand::Execute(GameObject&, Camera* camera) const
	{
		if (camera)
		{
			hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveCameraInputCommand Executed with x: %f, y: %f", m_x_delta, m_y_delta);
			GetGameModel().QueueModelCommand(std::make_unique<MoveCameraModelCommand>(*camera, Vector2f{ m_x_delta, m_y_delta }));
		}
	}
}