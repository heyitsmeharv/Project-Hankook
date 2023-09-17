#pragma once

#include "ModelCommand.h"

namespace hk
{
	class Camera;

	class MoveCameraModelCommand : public ModelCommand
	{
	public:
		MoveCameraModelCommand(Camera& camera, const Vector2f delta);

		void Execute() override;

	private:
		Camera*		m_camera = nullptr;
		Vector2f	m_delta;
	};
}