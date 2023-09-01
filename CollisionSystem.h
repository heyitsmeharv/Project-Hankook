#pragma once

#include <variant>
#include <vector>

#include "Circle.h"
#include "AABB.h"
#include "OBB.h"

namespace hk
{
	using CollisionObject = std::variant<Circle, AABB, OBB>;
	using CollisionList = std::vector<std::pair<const CollisionObject*, const CollisionObject*>>;

	class CollisionSystem
	{
	public:
		void RegisterCollisionObject	(CollisionObject* object);
		void DeregisterCollisionObject	(CollisionObject* object);

		bool AreObjectsColliding(const CollisionObject& object_a, const CollisionObject& object_b) const;

	private:
		CollisionList CheckObjectCollisions(const CollisionObject& queried_object);

	private:
		std::vector<CollisionObject*> m_collision_objects;
	};

	struct CollisionVisitor
	{
		//Circle
		bool operator() (const Circle& lhs, const Circle& rhs);
		bool operator() (const Circle& circle, const AABB& aabb);
		bool operator() (const Circle& circle, const OBB& obb);

		//AABB
		bool operator() (const AABB& lhs, const AABB& rhs);
		bool operator() (const AABB& aabb, const Circle& circle);
		bool operator() (const AABB& aabb, const OBB& obb);

		//OBB
		bool operator() (const OBB& lhs, const OBB& rhs);
		bool operator() (const OBB& obb, const Circle& circle);
		bool operator() (const OBB& obb, const AABB& aabb);
	};
}