#include "MoveObjectModelCommand.h"
#include "GameObject.h"

namespace hk
{
	MoveObjectModelCommand::MoveObjectModelCommand(GameObject& game_object, const Vector2f delta)
		: m_game_object(&game_object)
		, m_delta(delta)
	{
	}
	
	void MoveObjectModelCommand::Execute()
	{
		if (m_game_object)
		{
			m_game_object->MovePosition(m_delta);
		}
	}
}