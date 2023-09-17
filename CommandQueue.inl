#include "CommandQueue.h"

namespace hk
{
	template<typename T>
	void CommandQueue<T>::AddToQueue(std::unique_ptr<T>&& command)
	{
		m_command_queue.push_back(std::move(command));
	}

	template<typename T>
	void CommandQueue<T>::ProcessQueue()
	{
		for (auto& command : m_command_queue)
		{
			if (command)
			{
				command->Execute();
			}
		}
	}

	template<typename T>
	void CommandQueue<T>::ClearQueue()
	{
		m_command_queue.clear();
	}
}