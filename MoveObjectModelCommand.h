#pragma once

#include "ModelCommand.h"

namespace hk
{
	class GameObject;

	class MoveObjectModelCommand : public ModelCommand
	{
	public:
		MoveObjectModelCommand(GameObject& game_object, const Vector2f delta);

		void Execute() override;

	private:
		GameObject* m_game_object = nullptr;
		Vector2f	m_delta;
	};
}