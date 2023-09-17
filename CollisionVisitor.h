#pragma once

namespace hk
{
	struct AABB;
	struct Circle;
	struct OBB;

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