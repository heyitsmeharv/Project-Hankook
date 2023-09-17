#include "CollisionResolver.h"
#include "ErrorManager.h"
#include "GameObject.h"

namespace hk
{
	void ResolveCollisionVisitor::Visit(GameObject& rhs) const
	{
		int i = 10;
		i++;

		m_game_object.OnCollide(rhs);
	}

	void ResolveCollisionVisitor::Visit(PowerUpGameObject& rhs) const
	{
		int i = 10;
		i++;

		m_game_object.OnCollide(rhs);
	}

	void ResolveCollisionVisitor::Visit(ProjectileGameObject& rhs) const
	{
		int i = 10;
		i++;

		m_game_object.OnCollide(rhs);
	}
}