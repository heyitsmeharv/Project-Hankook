#pragma once

namespace hk
{
	class Engine;

	class BaseModel
	{
	public:
				 BaseModel(Engine& engine) : m_engine(engine) {}
		virtual ~BaseModel() {}

		virtual void Initialise	() = 0;
		virtual void Destroy	() = 0;
		virtual void Update		(const double delta_time) = 0;

	protected:
		Engine& m_engine;
	};
}