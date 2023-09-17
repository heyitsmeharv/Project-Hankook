#pragma once

#include "ResourceModifier.h"

namespace hk
{
	//May seem redundant but I think this is a cleaner API
	struct StepResourceModifierInitInfo
	{
		std::string id;
		double		modifier_amount = 0.0;
		double		modifier_rate = 0.0;
		double		current_timer = 0.0;
	};

	class StepResourceModifier : public ResourceModifier
	{
	public:
		StepResourceModifier(const StepResourceModifierInitInfo& init_info);

		virtual void Update(Resource& resource, const double delta_time) override;

	protected:
		virtual void ApplyModifier(Resource& resource) override;

	protected:
		std::string m_id;
		double		m_modifier_amount = 0.0;
		double		m_modifier_rate = 0.0;
		double		m_current_timer = 0.0;
	};
}