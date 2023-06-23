#include "ImGuiUser.h"
#include "ImGuiManager.h"

namespace hk
{
	ImGuiUser::ImGuiUser()
	{
		hk::ImGuiManager::RegisterUser(*this);
	}

	ImGuiUser::~ImGuiUser()
	{
		hk::ImGuiManager::DeregisterUser(*this);
	}
}