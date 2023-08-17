#pragma once

#include <string>

#include "ImGuiUser.h"
#include "ListenerReporter.h"
#include "Time.h"

namespace hk
{
	struct ResourceChangedEvent;

	struct ResourceInitInfo
	{
		std::string id;
		float		starting_amount = 0.0f;
		float		min_amount = 0.0f;
		float		max_amount = 100.0f;

		float		starting_decay_amount = 0.0f;
		TimeData	starting_decay_rate;
	};

	class Resource 
		: public IImGuiUser
		, public Utils::Reporter<ResourceChangedEvent>
	{
	public:
		Resource() = default;
		Resource(const ResourceInitInfo& init_info);

		void				Initialise(const TimePoint& current_time);

		void				OnTimeChange(const TimePoint& current_time);

		void				ApplyDecay(const TimePoint& current_time);

		const std::string&	Id() const;

		float				CurrentAmount() const;
		void				ChangeAmount(float amount_delta);
		void				SetCurrentAmount(float new_amount);

		float				CurrentDecayAmount() const;
		void				ChangeDecayAmount(float decay_delta);
		void				SetDecayAmount(float decay_amount);

		const TimeData&		CurrentDecayRate() const;
		void				ChangeDecayRate(const TimeData& decay_delta);
		void				SetDecayRate(const TimeData& decay_rate);

		void				AddToImGui() override;

	private:
		std::string m_id;
		float		m_current_amount;
		float		m_min_amount;
		float		m_max_amount;

		float		m_current_decay_amount;
		TimeData	m_current_decay_rate;
		TimePoint	m_last_decay_time;
		TimePoint	m_next_decay_time;
	};
}