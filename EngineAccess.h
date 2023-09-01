#pragma once

namespace hk
{
	class Engine;
}

namespace
{
	static inline hk::Engine* s_engine = nullptr;
}

namespace hk
{
	void RegisterEngine(Engine& _engine);
	Engine& GetEngine();
}