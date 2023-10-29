#include "ProjectileGameObject.h"

#include "ChangeResourceAmountModelCommand.h"
#include "CollisionResolver.h"
#include "GameModelAccess.h"
#include "GameModel.h"

namespace hk
{
	ProjectileGameObject::ProjectileGameObject(ProjectileGameObjectInitInfo& init_info)
		: GameObject(init_info)
		, m_direction(init_info.direction.AsNormalised())
		, m_velocity(init_info.velocity)
		, m_original_lifetime(init_info.lifetime)
		, m_current_lifetime(init_info.lifetime)
		, m_damage(init_info.damage)
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
			m_is_disabled = true;
		}

		GameObject::Update(delta_time);
	}

	void ProjectileGameObject::HitObject(GameObject& game_object)
	{
		GetGameModel().QueueModelCommand(std::make_unique<ChangeResourceAmountModelCommand>(game_object, "health", m_damage));
	}

	void ProjectileGameObject::Visit(const GameObjectCollisionVisitor& visitor)
	{
		visitor.Visit(*this);
	}
}