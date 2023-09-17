#pragma once

#include <string>

namespace hk
{
	class Resource;

	class ResourceModifier
	{
	public:
				 ResourceModifier(const std::string& id) : m_id(id) {}
		virtual ~ResourceModifier() {}

		const std::string& Id() const { return m_id; }

		virtual void Update(Resource& resource, const double delta_time) = 0;

	protected:
		virtual void ApplyModifier(Resource& resource) = 0;

		std::string m_id;
	};
}