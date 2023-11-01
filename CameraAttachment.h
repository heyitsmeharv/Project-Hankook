#pragma once

#include <entt/fwd.hpp>

namespace hk
{
	class CameraAttachment
	{
	public:
		virtual ~CameraAttachment() {}

		virtual void Update(entt::entity camera_entity, entt::registry& registry) = 0;

		bool IsEnabled		() const				{ return m_is_enabled; }
		void ToggleEnabled	()						{ m_is_enabled = !m_is_enabled; }
		void SetEnabled		(const bool is_enabled) { m_is_enabled = is_enabled; }

	protected:
		bool m_is_enabled = true;
	};
}