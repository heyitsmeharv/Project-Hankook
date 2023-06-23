#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "ImGuiUser.h"

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

	enum class ErrorSeverity
	{
		WARNING,
		FAULT,
		FATAL,

		NUM_OF_SEVERITY
	};

	struct ErrorInfo
	{
		ErrorSeverity severity = ErrorSeverity::WARNING;
		ErrorCategory category = ErrorCategory::NUM_OF_CATEGORIES;
		int count = 1;
	};

	void Warn(ErrorCategory category, const char* message, ...);
	namespace WarnIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...);
		void False(const bool expression, ErrorCategory category, const char* message, ...);
		void Null(const bool expression, ErrorCategory category, const char* message, ...);
	}

	void Fault(ErrorCategory category, const char* message, ...);
	namespace FaultIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...);
		void False(const bool expression, ErrorCategory category, const char* message, ...);
		void Null(const bool expression, ErrorCategory category, const char* message, ...);
	}

	void Fatal(ErrorCategory category, const char* message, ...);
	namespace FatalIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...);
		void False(const bool expression, ErrorCategory category, const char* message, ...);
		void Null(const bool expression, ErrorCategory category, const char* message, ...);
	}

	class ErrorManager : public ImGuiUser
	{
	public:
		void AddToImGui	() override;
		void AddError	(ErrorSeverity severity, ErrorCategory category, std::string&& message);

	private:
		std::unordered_map<std::string, hk::ErrorInfo> m_errors;

	//Singleton stuff
	public:
		static ErrorManager& Instance();

	private:
		static inline std::unique_ptr<ErrorManager> m_instance;
	};
}