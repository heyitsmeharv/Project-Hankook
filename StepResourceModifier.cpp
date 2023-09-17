#include "StepResourceModifier.h"
#include "Resource.h"

namespace hk
{
	StepResourceModifier::StepResourceModifier(const StepResourceModifierInitInfo& init_info)
		: ResourceModifier(init_info.id)
		, m_modifier_amount(init_info.modifier_amount)
		, m_modifier_rate(init_info.modifier_rate)
		, m_current_timer(0.0)
	{
	}

	void StepResourceModifier::Update(Resource& resource, const double delta_time)
	{
		m_current_timer += delta_time;

		if (m_current_timer >= m_modifier_rate)
		{
			ApplyModifier(resource);

			m_current_timer = 0.0;
		}
	}

	void StepResourceModifier::ApplyModifier(Resource& resource)
	{
		resource.ChangeAmount(m_modifier_amount);
	}
}