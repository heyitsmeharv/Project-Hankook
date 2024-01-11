#pragma once

#include <string>
#include <unordered_map>

#include "ImGuiUser.h"
#include "ListenerReporter.h"
#include "Resource.h"
#include "Time.h"

namespace hk
{
	struct ResourceChangedEvent;
	struct TimeChangedEvent;

	struct ResourceThreshold
	{
		float		amount = 0.0f;
		std::string text;
	};

	class PetModel 
		: public IImGuiUser
		, public utils::Listener<TimeChangedEvent>
		, public utils::Listener<ResourceChangedEvent>
	{
	public:
		PetModel(std::string&& name);

		void Initialise		(const TimePoint& current_time);
		void Update			(const double delta_time);

		void AddToImGui		() override;

		// Notifies
		void Notify			(const TimeChangedEvent& msg) override;
		void Notify			(const ResourceChangedEvent& msg) override;

	private:
		std::string m_name;
		float		m_age;
		Resource	m_happiness;
		Resource	m_fullness;

		std::unordered_map<std::string, std::vector<ResourceThreshold>> m_thresholds;
	};
}