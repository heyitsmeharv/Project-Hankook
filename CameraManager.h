#pragma once

#include <stack>

#include "Camera.h"

namespace hk
{
	class CameraManager
	{
	public:
		void			Update				();

		void			PushNewCamera		(const CameraInitInfo& init_info);
		void			PopCurrentCamera	();

		Camera*			CurrentCamera		();
		const Camera*	CurrentCamera		() const;

	private:
		std::stack<Camera> m_cameras;
	};
}