#include "CameraComponent.h"

#include "CameraAttachment.h"

namespace hk
{
	CameraComponent::CameraComponent()
	{
	}

	CameraComponent::~CameraComponent()
	{
	}

	CameraComponent::CameraComponent(CameraComponent&& rhs)
	{
		id = std::move(rhs.id);
		dimensions = std::move(rhs.dimensions);
		zoom = rhs.zoom;
		attachments = std::move(rhs.attachments);
	}

	CameraComponent& CameraComponent::operator=(CameraComponent&& rhs)
	{
		id = std::move(rhs.id);
		dimensions = std::move(rhs.dimensions);
		zoom = rhs.zoom;
		attachments = std::move(rhs.attachments);

		return *this;
	}
}