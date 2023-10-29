#pragma once

#include "ModelCommand.h"

namespace hk
{
	class Camera;

	class ChangeCameraZoomModelCommand : public ModelCommand
	{
	public:
		ChangeCameraZoomModelCommand(Camera& camera, const float delta);

		void Execute() override;

	private:
		Camera* m_camera = nullptr;
		float	m_delta;
	};
}