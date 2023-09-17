#pragma once

#include "GameObject.h"

namespace hk
{
	struct PowerUpGameObjectInitInfo : public GameObjectInitInfo
	{
		
	};

	class PowerUpGameObject : public GameObject
	{
	public:
		PowerUpGameObject(PowerUpGameObjectInitInfo& init_info);
		virtual ~PowerUpGameObject();

		void Update(const double delta_time) override;

		void Visit(const GameObjectCollisionVisitor& visitor) override;

	protected:
	};
}