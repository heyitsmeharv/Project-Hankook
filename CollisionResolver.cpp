#include "CollisionResolver.h"
#include "ErrorManager.h"

namespace hk
{
	void ResolveCollisionVisitor::Visit(GameObject&) const
	{
		//int i = 10;
		//i++;
		//
		//m_game_object.OnCollide(rhs);
	}

	void ResolveCollisionVisitor::Visit(PowerUpGameObject&) const
	{
		//int i = 10;
		//i++;

		//m_game_object.OnCollide(rhs);
	}

	void ResolveCollisionVisitor::Visit(ProjectileGameObject&) const
	{
		//int i = 10;
		//i++;

		//m_game_object.OnCollide(rhs);
	}
}