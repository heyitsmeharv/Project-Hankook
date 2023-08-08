#pragma once

#include "IModel.h"
#include "AutomaticClock.h"
#include "PetModel.h"

namespace hk
{
	struct TamagotchiModelInfo
	{

	};

	class TamagotchiModel final 
		: public IModel
		, public ImGuiUser
	{
	public:
		TamagotchiModel();

		void Initialise	() override;
		void Destroy	() override;
		void Update		(const double delta_time) override;

		void AddToImGui	() override;

	private:
		AutomaticClock m_clock;
		PetModel m_pet_model;
	};
}