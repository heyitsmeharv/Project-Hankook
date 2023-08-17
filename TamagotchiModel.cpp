#include "TamagotchiModel.h"

namespace hk
{
	TamagotchiModel::TamagotchiModel()
		: m_clock({ 24, 60, 60.0 }, { 5.0, { 0, 15, 0.0 } })
		, m_pet_model("test")
	{
	}

	void TamagotchiModel::Initialise()
	{
		m_clock.SetTime({ 7, 15, 20.5 , { 24, 60, 60.0 } });		//7h 15m 20.5s

		//m_clock.MoveForward ({ 0, 50,  0.0 });	// 8h   5m 20.5s
		//m_clock.MoveForward ({ 16, 0, 40.0 });	// 0h   6m  0.5s
		//m_clock.MoveBackward({ 1, 10,  1.6 });	//22h  56m  0.5s
		//m_clock.MoveBackward({ 36, 0, 0.0 });	//10h  56m  0.5s

		static_cast<Utils::Reporter<TimeChangedEvent>&>(m_clock).AddListener(m_pet_model);

		m_pet_model.Initialise(m_clock.GetTime());
	}

	void TamagotchiModel::Destroy()
	{

	}

	void TamagotchiModel::Update(const double delta_time)
	{
		m_clock.Update(delta_time);
	}

	void TamagotchiModel::AddToImGui()
	{
		if (ImGui::Begin("Tamagotchi Model"))
		{
			m_pet_model.AddToImGui();
		}

		ImGui::End();
	}
}