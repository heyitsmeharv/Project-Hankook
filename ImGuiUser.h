#pragma once

namespace hk
{
	class ImGuiUser
	{
	public:
					 ImGuiUser();
		 virtual	~ImGuiUser();

		virtual void AddToImGui() = 0;
	};
}