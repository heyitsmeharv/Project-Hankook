#include "PetModel.h"
#include "ResourceChangedEvent.h"
#include "TimeChangedEvent.h"

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
		happiness_info.starting_decay_amount = 47.5f;
		happiness_info.starting_decay_rate = TimeData{ 0, 15, 0.0 };

		m_happiness = Resource{ happiness_info };

		ResourceInitInfo fullness_info{};
		fullness_info.id = "Fullness";
		fullness_info.min_amount = 0.0f;
		fullness_info.max_amount = 100.0f;
		fullness_info.starting_amount = 100.0f;
		fullness_info.starting_decay_amount = 47.5f;
		fullness_info.starting_decay_rate = TimeData{ 0, 15, 0.0 };

		m_fullness = Resource{ fullness_info };

		static_cast<Utils::Reporter<ResourceChangedEvent>*>(&m_happiness)->AddListener(*this);
		static_cast<Utils::Reporter<ResourceChangedEvent>*>(&m_fullness)->AddListener(*this);

		m_thresholds =
		{
			{ "Happiness",
				{
					{ 50.0f, m_name + " is getting grumpy!\n" },
					{ 25.0f, m_name + " is very frustrated!\n" },
					{ 0.0f, m_name + " is angry and ran away!\n" }
				}
			},
			{ "Fullness", 
				{
					{ 75.0f, m_name + " could eat!\n" },
					{ 50.0f, m_name + " is hungry!\n" },
					{ 25.0f, m_name + " is really hungry!\n" },
					{ 10.0f, m_name + " is starving!\n" },
					{ 0.0f, m_name + " is famished and has run away!\n" }
				}
			}
		};
	}


	void PetModel::Initialise(const TimePoint& current_time)
	{
		m_happiness.Initialise(current_time);
		m_fullness.Initialise(current_time);
	}

	void PetModel::Notify(const ResourceChangedEvent& msg)
	{
		auto CheckResourceThreshold = [&](const Resource& resource) 
		{
			const auto& resource_thresholds_itr = m_thresholds.find(resource.Id());
			if (resource_thresholds_itr != m_thresholds.end())
			{
				auto threshold_itr = resource_thresholds_itr->second.rbegin();
				for (; threshold_itr != resource_thresholds_itr->second.rend(); threshold_itr++)
				{
					if (resource.CurrentAmount() <= threshold_itr->amount && msg.previous_amount > threshold_itr->amount)
					{
						break;
					}
				}

				if (threshold_itr != resource_thresholds_itr->second.rend())
				{
					printf("%s : %f \n", threshold_itr->text.data(), resource.CurrentAmount());
				}
			}
		};

		if (msg.id == m_happiness.Id())
		{
			CheckResourceThreshold(m_happiness);
		}
		else if(msg.id == m_fullness.Id())
		{
			CheckResourceThreshold(m_fullness);
		}
	}

	void PetModel::Notify(const TimeChangedEvent& msg)
	{
		//This seems suspect tbh, should the resource just listen?
		//Knee-jerk says yes but for some reason I'm reluctant as it causes more disconnected code
		m_happiness.OnTimeChange(msg.new_time);
		m_fullness.OnTimeChange(msg.new_time);
	}

	void PetModel::AddToImGui()
	{
		m_happiness.AddToImGui();
		m_fullness.AddToImGui();
	}
}