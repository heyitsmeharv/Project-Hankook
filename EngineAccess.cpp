#include "EngineAccess.h"

namespace hk
{
	void RegisterEngine(Engine& _engine)
	{
		s_engine = &_engine;
	}

	Engine& GetEngine()
	{
		return *s_engine;
	}
}