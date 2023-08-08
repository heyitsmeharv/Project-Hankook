#include "Resource.h"

#include <algorithm>

namespace hk
{
	Resource::Resource(const ResourceInitInfo& init_info)
		: m_id(init_info.id)
		, m_current_amount(init_info.starting_amount)
		, m_min_amount(init_info.min_amount)
		, m_max_amount(init_info.max_amount)
		, m_current_decay_amount(init_info.starting_decay_amount)
		, m_current_decay_rate(init_info.starting_decay_rate)
		, m_last_decay_time()
		, m_next_decay_time()
	{
	}

	void Resource::Initialise(const TimePoint& current_time)
	{
		m_last_decay_time = current_time;
		m_next_decay_time = current_time + m_current_decay_rate;
		m_next_decay_time.Wrap();
	}

	void Resource::OnTimeChange(const TimePoint& current_time)
	{
		if (current_time >= m_next_decay_time)
		{
			ApplyDecay(current_time);
		}
	}

	void Resource::ApplyDecay(const TimePoint& current_time)
	{
		ChangeAmount(-m_current_amount);

		m_last_decay_time = current_time;
		m_next_decay_time = current_time + m_current_decay_rate;
		m_next_decay_time.Wrap();
	}

	float Resource::CurrentAmount() const
	{
		return m_current_amount;
	}

	void Resource::ChangeAmount(float amount_delta)
	{
		m_current_amount += amount_delta;
		m_current_amount = std::clamp(m_current_amount, m_min_amount, m_max_amount);
	}

	void Resource::SetCurrentAmount(float new_amount)
	{
		m_current_amount = new_amount;
		m_current_amount = std::clamp(m_current_amount, m_min_amount, m_max_amount);
	}

	float Resource::CurrentDecayAmount() const
	{
		return m_current_decay_amount;
	}

	void Resource::ChangeDecayAmount(float decay_delta)
	{
		m_current_decay_amount += decay_delta;
	}

	void Resource::SetDecayAmount(float decay_amount)
	{
		m_current_decay_amount = decay_amount;
	}

	const TimeData& Resource::CurrentDecayRate() const
	{
		return m_current_decay_rate;
	}

	void Resource::ChangeDecayRate(const TimeData& decay_rate_delta)
	{
		m_current_decay_rate += decay_rate_delta;
	}

	void Resource::SetDecayRate(const TimeData& decay_rate)
	{
		m_current_decay_rate = decay_rate;
	}

	void Resource::AddToImGui()
	{
		if (ImGui::TreeNode(m_id.data(), "%s - (%f/%f)", m_id.data(), m_current_amount, m_max_amount))
		{
			ImGui::ProgressBar(m_current_amount / m_max_amount);

			if (ImGui::InputFloat("Change Amount", &m_current_amount, 1.0f, 10.0f))
			{
				m_current_amount = std::clamp(m_current_amount, m_min_amount, m_max_amount);
			}

			if (ImGui::TreeNode("Details"))
			{
				ImGui::Text("Current Delay Amount: %f", m_current_decay_amount);
				ImGui::Text("Last Decay Time: %d(h) %d(m) %f(s)", m_last_decay_time.hour, m_last_decay_time.minute, m_last_decay_time.second);
				ImGui::Text("Next Decay Time: %d(h) %d(m) %f(s)", m_next_decay_time.hour, m_next_decay_time.minute, m_next_decay_time.second);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
}