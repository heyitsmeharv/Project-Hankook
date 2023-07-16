#include "ProjectileGameObject.h"

namespace hk
{
	ProjectileGameObject::ProjectileGameObject(ProjectileGameObjectInitInfo& init_data)
		: GameObject(init_data)
		, m_direction(init_data.direction.AsNormalised())
		, m_velocity(init_data.velocity)
		, m_original_lifetime(init_data.lifetime)
		, m_current_lifetime(init_data.lifetime)
	{
	}

	ProjectileGameObject::~ProjectileGameObject()
	{
	}

	void ProjectileGameObject::Update(const double delta_time)
	{
		m_current_lifetime -= delta_time;

		if (m_original_lifetime <= 0.0 || m_current_lifetime > 0.0)
		{
			MovePosition((float)(m_direction.x * m_velocity), (float)(m_direction.y * m_velocity));
		}
		else
		{
			m_is_alive = false;
		}

		GameObject::Update(delta_time);
	}
}