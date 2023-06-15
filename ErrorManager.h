#pragma once

#include <unordered_map>
#include <string>

namespace hk
{
	enum class ErrorCategory
	{
		GFX,
		INPUT,
		GAME_LOGIC,
		UNCATEGORISED,

		NUM_OF_CATEGORIES
	};

	struct ErrorInfo
	{
		ErrorCategory category = ErrorCategory::NUM_OF_CATEGORIES;
		int count = 1;
	};

	class ErrorManager
	{
	public:
		static void Error(ErrorCategory category, const char* message, ...);

		static void AddToImGui();

	private:
		static inline std::unordered_map<std::string, hk::ErrorInfo> m_errors;
	};
}