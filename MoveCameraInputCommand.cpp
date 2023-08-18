#include "MoveCameraInputCommand.h"
#include "Logger.h"

#include "Camera.h"

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

	void MoveCameraInputCommand::Execute(GameObject&, Camera* camera) const
	{
		if (camera)
		{
			hk::Logger::Instance().AddEntry(hk::LogCategory::COMMANDS, "MoveCameraInputCommand Executed with x: %f, y: %f", m_x_delta, m_y_delta);
			camera->MovePosition(m_x_delta, m_y_delta);
		}
	}
}