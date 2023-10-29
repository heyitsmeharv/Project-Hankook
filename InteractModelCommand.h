#pragma once

#include <string>

#include "ModelCommand.h"

namespace hk
{
	class GameObject;

	class InteractModelCommand : public ModelCommand
	{
	public:
		InteractModelCommand(GameObject& game_object);

		void Execute() override;

	private:
		GameObject* m_game_object = nullptr;
	};
}