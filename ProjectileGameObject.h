#pragma once

#include "GameObject.h"

namespace hk
{
	struct ProjectileGameObjectInitInfo : public GameObjectInitInfo
	{
		Vector2f direction = { 0.0f, 0.0f };
		double velocity = 1.0;
		double lifetime = -1.0;
		double damage = 10;
	};

	class ProjectileGameObject : public GameObject
	{
	public:
		ProjectileGameObject(ProjectileGameObjectInitInfo& init_info);
		virtual ~ProjectileGameObject();

		void Update(const double delta_time) override;

		void Visit(const GameObjectCollisionVisitor& visitor) override;

		void HitObject(GameObject& game_object);

	protected:
		Vector2f	m_direction;
		double		m_velocity;
		double		m_original_lifetime;
		double		m_current_lifetime;
		double		m_damage;
	};
}