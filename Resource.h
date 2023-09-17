#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ImGuiUser.h"
#include "ListenerReporter.h"
#include "ResourceModifier.h"

namespace hk
{
	struct ResourceChangedEvent;

	using ModifierList = std::vector<ResourceModifier*>;

	struct ResourceInitInfo
	{
		std::string		id;
		double			starting_amount = 0.0;
		double			min_amount = 0.0;
		double			max_amount = 100.0;
		ModifierList	modifiers;
	};


	class Resource 
		: public IImGuiUser
		, public Utils::Reporter<ResourceChangedEvent>
	{
	public:
		 Resource();
		 Resource(const ResourceInitInfo& init_info);
		~Resource();

		void				Initialise			(const ResourceInitInfo& init_info);

		void				Update				(const double delta_time);

		const std::string&	Id					() const;

		double				CurrentAmount		() const;
		void				ChangeAmount		(double amount_delta);
		void				SetCurrentAmount	(double new_amount);

		void				AddModifier			(ResourceModifier* new_modifier);

		void				AddToImGui			() override;

	private:
		std::string			m_id;
		double				m_current_amount;
		double				m_min_amount;
		double				m_max_amount;
		ModifierList		m_modifiers;
	};
}