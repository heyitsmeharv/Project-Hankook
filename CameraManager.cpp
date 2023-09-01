#include "CameraManager.h"

namespace hk
{
	void CameraManager::Update()
	{
		if (m_cameras.empty() == false)
		{
			m_cameras.top().Update();
		}
	}

	void CameraManager::PushNewCamera(const CameraInitInfo& init_info)
	{
		m_cameras.emplace(init_info);
	}

	void CameraManager::PopCurrentCamera()
	{
		m_cameras.pop();
	}

	Camera* CameraManager::CurrentCamera()
	{
		if (m_cameras.empty())
		{
			return nullptr;
		}

		return &m_cameras.top();
	}

	const Camera* CameraManager::CurrentCamera() const
	{
		return CurrentCamera();
	}
}