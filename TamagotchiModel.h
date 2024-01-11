#pragma once

#include "BaseModel.h"
#include "AutomaticClock.h"
#include "PetModel.h"

namespace hk
{
	struct TamagotchiModelInfo
	{

	};

	class TamagotchiModel final 
		: public BaseModel
		, public ImGuiUser
	{
	public:
		TamagotchiModel(Engine& engine);

		void Initialise	() override;
		void Destroy	() override;
		void Update		(const double delta_time) override;

		void AddToImGui	() override;

	private:
		AutomaticClock m_clock;
		PetModel m_pet_model;
	};
}