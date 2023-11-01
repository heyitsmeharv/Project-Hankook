#pragma once

#include <entt/fwd.hpp>
#include <memory>
#include <vector>

namespace hk
{
	template<typename T>
	class CommandQueue
	{
	public:
		void AddToQueue(std::unique_ptr<T>&& command);
		void ProcessQueue(entt::registry& registry);
		void ClearQueue();

	private:
		std::vector<std::unique_ptr<T>> m_command_queue;
	};
}

#include "CommandQueue.inl"