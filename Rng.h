#pragma once

#include <random>

namespace hk
{
	class Rng
	{
	public:
		static void			SetSeed(unsigned int seed);

		static int GetNext();
		static int GetInRange(int lower_bound, int upper_bound);

	private:
		static inline std::mt19937 m_rng;
	};
}