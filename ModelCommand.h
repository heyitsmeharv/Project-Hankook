#pragma once

#include "Vector2.h"

namespace hk
{
	class ModelCommand
	{
	public:
		virtual ~ModelCommand() {}
		virtual void Execute() = 0;
	};
}