#include "PetModel.h"

namespace hk
{
	PetModel::PetModel(std::string&& name)
		: m_name(std::move(name))
		, m_age(0.0f)
	{
		ResourceInitInfo happiness_info{};
		happiness_info.id = "Happiness";
		happiness_info.min_amount = 0.0f;
		happiness_info.max_amount = 100.0f;
		happiness_info.starting_amount = 100.0f;
		happiness_info.starting_decay_amount = 5.0f;
		happiness_info.starting_decay_rate = TimeData{ 0, 15, 0.0 };

		m_happiness = Resource{ happiness_info };

		ResourceInitInfo fullness_info{};
		fullness_info.id = "Fullness";
		fullness_info.min_amount = 0.0f;
		fullness_info.max_amount = 100.0f;
		fullness_info.starting_amount = 100.0f;
		fullness_info.starting_decay_amount = 5.0f;
		fullness_info.starting_decay_rate = TimeData{ 0, 15, 0.0 };

		m_fullness = Resource{ fullness_info };
	}


	void PetModel::Initialise(const TimePoint& current_time)
	{
		m_happiness.Initialise(current_time);
		m_fullness.Initialise(current_time);
	}

	void PetModel::OnTimeChange(const TimePoint& current_time)
	{
		m_happiness.OnTimeChange(current_time);
		if (m_happiness.CurrentAmount() <= 0.0f)
		{
			printf("%s felt unhappy and ran away \n", m_name.data());
		}

		m_fullness.OnTimeChange(current_time);
		if (m_fullness.CurrentAmount() <= 0.0f)
		{
			printf("%s was famished and ran way \n", m_name.data());
		}
	}

	void PetModel::AddToImGui()
	{
		m_happiness.AddToImGui();
		m_fullness.AddToImGui();
	}
}