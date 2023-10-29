#include "Resource.h"
#include "ResourceChangedEvent.h"

#include <algorithm>

namespace hk
{
	Resource::Resource()
		: m_key()
		, m_current_amount(0.0)
		, m_min_amount(0.0)
		, m_max_amount(0.0)
		, m_modifiers()
	{
	}

	Resource::Resource(const ResourceInitInfo& init_info)
	{
		Initialise(init_info);
	}

	Resource::~Resource()
	{
		for (auto& modifier : m_modifiers)
		{
			delete modifier;
			modifier = nullptr;
		}
		m_modifiers.clear();
	}

	void Resource::Initialise(const ResourceInitInfo& init_info)
	{
		m_key = init_info.key;
		m_current_amount = init_info.starting_amount;
		m_min_amount = init_info.min_amount;
		m_max_amount = init_info.max_amount;
		m_modifiers = init_info.modifiers;
	}

	void Resource::Update(const double delta_time)
	{
		for (auto& modifier : m_modifiers)
		{
			modifier->Update(*this, delta_time);
		}
	}

	const std::string& Resource::Key() const
	{
		return m_key;
	}

	double Resource::CurrentAmount() const
	{
		return m_current_amount;
	}

	void Resource::ChangeAmount(double amount_delta)
	{
		ResourceChangedEvent msg;
		msg.id = m_key;
		msg.previous_amount = m_current_amount;
		msg.change_in_amount = amount_delta;

		m_current_amount += amount_delta;
		m_current_amount = std::clamp(m_current_amount, m_min_amount, m_max_amount);

		msg.new_amount = m_current_amount;

		NotifyListeners(msg);
	}

	void Resource::SetCurrentAmount(double new_amount)
	{
		ResourceChangedEvent msg;
		msg.id = m_key;
		msg.previous_amount = m_current_amount;
		msg.change_in_amount = new_amount - m_current_amount;
		msg.new_amount = new_amount;

		m_current_amount = std::clamp(new_amount, m_min_amount, m_max_amount);

		NotifyListeners(msg);
	}

	void Resource::AddModifier(ResourceModifier* new_modifier)
	{
		m_modifiers.push_back(new_modifier);
	}

	void Resource::AddToImGui()
	{
		if (ImGui::TreeNode(m_key.data(), "%s - (%f/%f)", m_key.data(), m_current_amount, m_max_amount))
		{
			ImGui::ProgressBar(static_cast<float>(m_current_amount / m_max_amount));

			if (ImGui::InputDouble("Change Amount", &m_current_amount, 1.0f, 10.0f))
			{
				m_current_amount = std::clamp(m_current_amount, m_min_amount, m_max_amount);
			}

			if (ImGui::TreeNode("Details"))
			{
				

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
}