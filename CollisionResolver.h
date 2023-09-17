#pragma once

namespace hk
{
	class GameObject;
	class PowerUpGameObject;
	class ProjectileGameObject;

	struct GameObjectCollisionVisitor
	{
		virtual void Visit(GameObject&) const = 0;
		virtual void Visit(PowerUpGameObject&) const = 0;
		virtual void Visit(ProjectileGameObject&) const = 0;
	};

	class ResolveCollisionVisitor : public GameObjectCollisionVisitor
	{
	public:
		ResolveCollisionVisitor(GameObject& game_object) : m_game_object(game_object) {}

		void Visit(GameObject&) const override;
		void Visit(PowerUpGameObject&) const override;
		void Visit(ProjectileGameObject&) const override;

	private:
		GameObject& m_game_object;
	};
}