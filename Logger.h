#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ImGuiUser.h"

namespace hk
{
	enum class LogCategory : unsigned int
	{
		GENERAL_INFO = 1 << 0,
		INPUT		= 1 << 1,
		COMMANDS	= 1 << 2,
		GFX			= 1 << 3,

		END_OF_CATEGORIES = 1 << 4
	};

	struct LogEntry
	{
		LogEntry(LogCategory _category, std::string&& _message)
			: category(_category)
			, message(std::move(_message))
		{
		}

		LogCategory category;
		std::string message;
	};

	class Logger : public ImGuiUser
	{
	public:
		void AddEntry(LogCategory category, const char* message, ...);

		const std::string& GetCategoryAsString(const LogCategory category);

		void AddToImGui();

	private:
		std::vector<LogEntry> m_entries;

	//Singleton stuff
	public:
		static Logger& Instance();

	private:
		static inline std::unique_ptr<Logger> m_instance;
	};
}