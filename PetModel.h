#pragma once

#include <string>

#include "ImGuiUser.h"
#include "IModel.h"
#include "Resource.h"
#include "Time.h"

namespace hk
{
	class PetModel : public IImGuiUser
	{
	public:
		PetModel(std::string&& name);

		void Initialise		(const TimePoint& current_time);
		void OnTimeChange	(const TimePoint& current_time);

		void AddToImGui		() override;

	private:
		std::string m_name;
		float		m_age;
		Resource	m_happiness;
		Resource	m_fullness;
	};
}