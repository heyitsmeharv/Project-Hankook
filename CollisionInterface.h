#pragma once

namespace hk
{
	struct GameObjectCollisionVisitor;
	class  GameObject;
	class  PowerUpGameObject;
	class  ProjectileGameObject;

	struct CollisionInterface
	{
		virtual void	Visit(const GameObjectCollisionVisitor& visitor) = 0;

		virtual void	HandleCollision(GameObject&) = 0;

		virtual void	OnCollide(GameObject&) {}
		virtual void	OnCollide(PowerUpGameObject&) {}
		virtual void	OnCollide(ProjectileGameObject&) {}

	};
}