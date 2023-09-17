#include "MoveCameraModelCommand.h"
#include "Camera.h"

namespace hk
{
	MoveCameraModelCommand::MoveCameraModelCommand(Camera& Camera, const Vector2f delta)
		: m_camera(&Camera)
		, m_delta(delta)
	{
	}

	void MoveCameraModelCommand::Execute()
	{
		if (m_camera)
		{
			m_camera->MovePosition(m_delta);
		}
	}
}