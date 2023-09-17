#pragma once

#include <vector>

namespace hk
{
	class Collidable;

	using CollisionList = std::vector<std::pair<Collidable*, Collidable*>>;

	class CollisionSystem
	{
	public:
		void Update();

		void RegisterCollidable		(Collidable& collidable);
		void DeregisterCollidable	(Collidable& collidable);

		bool AreObjectsColliding	(const Collidable& object_a, const Collidable& object_b) const;

	private:
		std::vector<Collidable*> m_collidables;
	};
}