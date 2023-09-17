#include "PowerUpGameObject.h"
#include "CollisionResolver.h"

namespace hk
{
	PowerUpGameObject::PowerUpGameObject(PowerUpGameObjectInitInfo& init_info)
		: GameObject(init_info)
	{
	}

	PowerUpGameObject::~PowerUpGameObject()
	{
	}

	void PowerUpGameObject::Update(const double delta_time)
	{


		GameObject::Update(delta_time);
	}

	void PowerUpGameObject::Visit(const GameObjectCollisionVisitor& visitor)
	{
		visitor.Visit(*this);
	}
}