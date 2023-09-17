#include "EngineAccess.h"
#include "GameModelAccess.h"

#include "Engine.h"

namespace hk
{
	GameModel& GetGameModel()
	{
		return GetEngine().GetGameModel();
	}
}