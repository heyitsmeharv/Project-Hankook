#pragma once

#include <variant>

#include "Circle.h"
#include "AABB.h"
#include "OBB.h"

namespace hk
{
	using BoundingVolume = std::variant<Circle, AABB, OBB>;

	class GameObject;

	class Collidable
	{
	public:
		Collidable(BoundingVolume bounding_volume)
			: m_bounding_volume(bounding_volume)
			, m_owner(nullptr)
		{
		}
	
		const BoundingVolume&		GetBoundingVolume	() const { return m_bounding_volume; }
		GameObject*					GetOwner			()		 { return m_owner; }
	
		void						SetOwner			(GameObject& owner) { m_owner = &owner; }
	
	protected:
		BoundingVolume	m_bounding_volume;
		GameObject*		m_owner = nullptr;
	};
}