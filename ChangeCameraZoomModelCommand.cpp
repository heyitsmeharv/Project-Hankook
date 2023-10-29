#include "ChangeCameraZoomModelCommand.h"

#include "Camera.h"

namespace hk
{
	ChangeCameraZoomModelCommand::ChangeCameraZoomModelCommand(Camera& Camera, const float delta)
		: m_camera(&Camera)
		, m_delta(delta)
	{
	}

	void ChangeCameraZoomModelCommand::Execute()
	{
		if (m_camera)
		{
			m_camera->ChangeZoom(m_delta);
		}
	}
}