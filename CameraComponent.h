#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Vector2.h"

namespace hk
{
	class CameraAttachment;

	struct CameraComponent
	{
		std::string										id;
		Vector2i										dimensions;
		float											zoom = 1.0f;
		std::vector<std::unique_ptr<CameraAttachment>>	attachments;

		//unique_ptrs wreaking fucking havoc as per usual
		  CameraComponent();
		 ~CameraComponent();
		
		CameraComponent(CameraComponent&& rhs);
		CameraComponent& operator=(CameraComponent&& rhs);
	};
}