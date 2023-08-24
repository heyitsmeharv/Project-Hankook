#pragma once

namespace hk
{
	class Camera;

	class CameraAttachment
	{
	public:
		virtual ~CameraAttachment() {}

		virtual void Update(Camera&) = 0;

		bool IsEnabled		() const				{ return m_is_enabled; }
		void ToggleEnabled	()						{ m_is_enabled = !m_is_enabled; }
		void SetEnabled		(const bool is_enabled) { m_is_enabled = is_enabled; }

	protected:
		bool m_is_enabled = true;
	};
}