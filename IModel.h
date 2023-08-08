#pragma once

namespace hk
{
	class IModel
	{
	public:
		virtual void Initialise	() = 0;
		virtual void Destroy	() = 0;
		virtual void Update		(const double delta_time) = 0;
	};
}