#pragma once

#include <vector>
#include <algorithm>

namespace hk::Utils
{
	template<typename T>
	class Listener
	{
	public:
		virtual void Notify(const T&) = 0;
	};

	template<typename T>
	class Reporter
	{
	public:
		void AddListener(Listener<T>& listener)
		{
			m_listeners.push_back(&listener);
		}

		void RemoveListener(const Listener<T>& to_remove)
		{
			const auto& itr = std::find_if(m_listeners.begin(), m_listeners.end(), [&to_remove](const auto& listener) { return to_remove == listener; });
			if (itr != m_listeners.end())
			{
				m_listeners.erase(itr);
			}
		}

		void NotifyListeners(const T& msg)
		{
			for (const auto& listener : m_listeners)
			{
				listener->Notify(msg);
			}
		}

	private:
		std::vector<Listener<T>*> m_listeners;
	};
}