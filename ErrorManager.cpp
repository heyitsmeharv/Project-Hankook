#include "ErrorManager.h"

#include <stdio.h>
#include <stdarg.h>

#include "imgui/imgui.h"

namespace
{
	const std::string& SeverityString(const hk::ErrorSeverity severity)
	{
		static const std::string ph = "severity not found";
		static const std::unordered_map<hk::ErrorSeverity, std::string> lookup
		{
			{ hk::ErrorSeverity::WARNING,	"Warning" },
			{ hk::ErrorSeverity::FAULT,		"Fault" },
			{ hk::ErrorSeverity::FATAL,		"Fatal" },
		};

		const auto& itr = lookup.find(severity);
		return itr != lookup.end() ? itr->second : ph;
	}
}

namespace hk
{
	void Warn(ErrorCategory category, const char* message, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		hk::ErrorManager::Instance().AddError(hk::ErrorSeverity::WARNING, category, buffer);
	}

	namespace WarnIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...)
		{
			if (expression)
			{
				va_list args{};
				hk::Warn(category, message, args);
			}
		}

		void False(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::WarnIf::True(expression == false, category, message, args);
		}

		void Null(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::WarnIf::False(expression, category, message, args);
		}
	}

	void Fault(ErrorCategory category, const char* message, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		hk::ErrorManager::Instance().AddError(hk::ErrorSeverity::FAULT, category, buffer);
	}

	namespace FaultIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...)
		{
			if (expression)
			{
				va_list args{};
				hk::Fault(category, message, args);
			}
		}

		void False(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::FaultIf::True(expression == false, category, message, args);
		}

		void Null(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::FaultIf::False(expression, category, message, args);
		}
	}

	void Fatal(ErrorCategory category, const char* message, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		hk::ErrorManager::Instance().AddError(hk::ErrorSeverity::FATAL, category, buffer);
	}

	namespace FatalIf
	{
		void True(const bool expression, ErrorCategory category, const char* message, ...)
		{
			if (expression)
			{
				va_list args{};
				hk::Fatal(category, message, args);
			}
		}

		void False(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::FatalIf::True(expression == false, category, message, args);
		}

		void Null(const bool expression, ErrorCategory category, const char* message, ...)
		{
			va_list args{};
			hk::FatalIf::False(expression, category, message, args);
		}
	}

	void ErrorManager::AddError(ErrorSeverity severity, ErrorCategory category, std::string&& message)
	{
		auto [itr, did_insert] = m_errors.insert({ std::move(message), hk::ErrorInfo{ severity, category, 1 }});
		if (did_insert == false)
		{
			itr->second.count++;
		}
	}

	void ErrorManager::AddToImGui()
	{
		ImGui::Begin("Error List");

		for (int i = static_cast<int>(ErrorSeverity::NUM_OF_SEVERITY) - 1; i >= 0; --i)
		{
			std::string table_id = SeverityString(static_cast<ErrorSeverity>(i));
			ImGui::Text(table_id.data());

			static ImGuiTableFlags flags =
				ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable
				| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;

			if (ImGui::BeginTable(table_id.data(), 2, flags))
			{
				ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupColumn("Message");
				ImGui::TableHeadersRow();

				for (const auto& [error_msg, error_info] : m_errors)
				{
					if (static_cast<int>(error_info.severity) == i)
					{
						ImGui::TableNextRow();

						ImGui::TableNextColumn();
						ImGui::Text("%d", error_info.count);

						ImGui::TableNextColumn();
						ImGui::Text("%s", error_msg.data());
					}
				}

				ImGui::EndTable();
				ImGui::NewLine();
			}
		}

		ImGui::End();
	}

	ErrorManager& ErrorManager::Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<ErrorManager>();
		}

		return *m_instance;
	}
}