#include <algorithm>

#include "Collidable.h"
#include "CollisionResolver.h"
#include "CollisionSystem.h"
#include "CollisionVisitor.h"

namespace hk
{
	void CollisionSystem::Update()
	{
		CollisionList colliding_objects;
		CollisionVisitor visitor;

		for (int i = 0; i < m_collidables.size(); i++)
		{
			Collidable* lhs = m_collidables[i];

			for (int j = i + 1; j < m_collidables.size(); ++j)
			{
				Collidable* rhs = m_collidables[j];
				if (std::visit(visitor, lhs->GetBoundingVolume(), rhs->GetBoundingVolume()))
				{
					colliding_objects.push_back({ lhs, rhs });
				}
			}
		}

		//for (auto& collision : colliding_objects)
		//{
		//	collision.first->GetOwner()->HandleCollision(*collision.second->GetOwner());
		//}
	}

	bool CollisionSystem::AreObjectsColliding(const Collidable& object_a, const Collidable& object_b) const
	{
		return std::visit(CollisionVisitor{}, object_a.GetBoundingVolume(), object_b.GetBoundingVolume());
	}

	void CollisionSystem::RegisterCollidable(Collidable& collidable)
	{
		m_collidables.push_back(&collidable);
	}

	void CollisionSystem::DeregisterCollidable(Collidable& collidable)
	{
		const auto& itr = std::find(m_collidables.begin(), m_collidables.end(), &collidable);
		if (itr != m_collidables.end())
		{
			m_collidables.erase(itr);
		}
	}
}