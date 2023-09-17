#include "CollisionVisitor.h"

#include "AABB.h"
#include "Circle.h"
#include "OBB.h"

namespace hk
{
	//Circle
	bool CollisionVisitor::operator() (const Circle& lhs, const Circle& rhs)
	{
		const Vector2f centre_delta = rhs.position - lhs.position;
		const float radius_sum_sq = (lhs.radius * lhs.radius) + (rhs.radius * rhs.radius);

		return centre_delta.MagnitudeSquared() <= radius_sum_sq;
	}

	bool CollisionVisitor::operator() (const Circle& circle, const AABB& aabb)
	{
		const Vector2f centre_delta = circle.position - aabb.position;
		const float radius_sum_sq = circle.radius * circle.radius;

		return centre_delta.MagnitudeSquared() <= radius_sum_sq;
	}

	bool CollisionVisitor::operator() (const Circle&, const OBB&)
	{
		//TODO: IMPLEMENT THIS
		return false;
	}

	//AABB
	bool CollisionVisitor::operator() (const AABB& lhs, const AABB& rhs)
	{
		if (lhs.position.x <= rhs.position.x + rhs.dimensions.x && (lhs.position.x + lhs.dimensions.x) >= rhs.position.x)
		{
			if (lhs.position.y <= rhs.position.y + rhs.dimensions.y && (lhs.position.y + lhs.dimensions.y) >= rhs.position.y)
			{
				return true;
			}
		}

		return false;
	}

	bool CollisionVisitor::operator() (const AABB& aabb, const Circle& circle)
	{
		return operator()(circle, aabb);
	}

	bool CollisionVisitor::operator() (const AABB&, const OBB&)
	{
		//TODO: IMPLEMENT THIS
		return false;
	}

	//OBB
	bool CollisionVisitor::operator() (const OBB&, const OBB&)
	{
		//TODO: IMPLEMENT THIS
		return false;
	}

	bool CollisionVisitor::operator() (const OBB& obb, const Circle& circle)
	{
		return operator()(circle, obb);
	}

	bool CollisionVisitor::operator() (const OBB& obb, const AABB& aabb)
	{
		return operator()(aabb, obb);
	}
}