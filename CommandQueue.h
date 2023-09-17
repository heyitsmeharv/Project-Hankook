#pragma once

#include <memory>
#include <vector>

namespace hk
{
	template<typename T>
	class CommandQueue
	{
	public:
		void AddToQueue(std::unique_ptr<T>&& command);
		void ProcessQueue();
		void ClearQueue();

	private:
		std::vector<std::unique_ptr<T>> m_command_queue;
	};
}

#include "CommandQueue.inl"