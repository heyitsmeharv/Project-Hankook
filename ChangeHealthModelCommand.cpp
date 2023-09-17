#include "ChangeHealthModelCommand.h"
#include "GameObject.h"

namespace hk
{
	ChangeHealthModelCommand::ChangeHealthModelCommand(GameObject& game_object, const double delta)
		: m_game_object(&game_object)
		, m_delta(delta)
	{
	}

	void ChangeHealthModelCommand::Execute()
	{
		if (m_game_object)
		{
			m_game_object->ChangeHealth(m_delta);
		}
	}
}