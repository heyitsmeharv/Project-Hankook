#pragma once

#include <string>

#include "ModelCommand.h"

namespace hk
{
	class GameObject;

	class ChangeResourceAmountModelCommand : public ModelCommand
	{
	public:
		ChangeResourceAmountModelCommand(GameObject& game_object, const std::string& resource_key, const double delta);

		void Execute() override;

	private:
		GameObject* m_game_object = nullptr;
		std::string m_resource_key;
		double		m_delta;
	};
}