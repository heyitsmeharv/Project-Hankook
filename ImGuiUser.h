#pragma once

#include "imgui/imgui.h"

namespace hk
{
	class IImGuiUser
	{
	public:
		virtual void AddToImGui() = 0;
	};

	class ImGuiUser : public IImGuiUser
	{
	public:
					 ImGuiUser();
		 virtual	~ImGuiUser();
	};
}