#include "Rng.h"
#include "Logger.h"

namespace hk
{
	void Rng::SetSeed(unsigned int seed)
	{
		m_rng.seed(seed);
		hk::Logger::Instance().AddEntry(hk::LogCategory::GENERAL_INFO, "RNG Seed set to %u", seed);
	}

	int Rng::GetNext()
	{
		return m_rng();
	}

	int Rng::GetInRange(const int low_bound, const int high_bound)
	{
		std::uniform_int_distribution<> bounds{ low_bound, high_bound };
		return bounds(m_rng);
	}
}