#pragma once

#include "ModelCommand.h"

namespace hk
{
	class GameObject;

	class ChangeHealthModelCommand : public ModelCommand
	{
	public:
		ChangeHealthModelCommand(GameObject& game_object, const double delta);

		void Execute() override;

	private:
		GameObject* m_game_object = nullptr;
		double		m_delta;
	};
}