#include "Logger.h"

#include <stdarg.h>
#include <unordered_map>
#include <limits>

namespace hk
{
	Logger& Logger::Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<Logger>();
		}

		return *m_instance;
	}

	void Logger::AddEntry(LogCategory category, const char* message, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		m_entries.emplace_back(category, buffer);
	}

	const std::string& Logger::GetCategoryAsString(const LogCategory category)
	{
		static const std::string unknown_category = "UNKNOWN CATEGORY";
		static const std::unordered_map<LogCategory, std::string> lookup = 
		{
			{ LogCategory::GENERAL_INFO, "GENERAL"},
			{ LogCategory::INPUT, "INPUT"},
			{ LogCategory::COMMANDS, "COMMANDS" },
			{ LogCategory::GFX, "GFX" },
		};

		const auto& itr = lookup.find(category);
		return itr != lookup.end() ? itr->second : unknown_category;
	}

	void Logger::AddToImGui()
	{
		ImGui::Begin("Log");

		static unsigned int enabled_categories = std::numeric_limits<int>::max();
		for (int i = 1; i < static_cast<int>(LogCategory::END_OF_CATEGORIES); i = i << 1)
		{
			//ImGui::SameLine();
			ImGui::CheckboxFlags(GetCategoryAsString(static_cast<LogCategory>(i)).data(), &enabled_categories, i);
		}

		static ImGuiTableFlags flags =
			ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable
			| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;

		if (ImGui::BeginTable("Log", 2, flags))
		{
			ImGui::TableSetupColumn("Category", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Message");
			ImGui::TableHeadersRow();

			for (const auto& entry : m_entries)
			{
				if ((static_cast<unsigned int>(entry.category) & enabled_categories) > 0)
				{
					ImGui::TableNextRow();

					ImGui::TableNextColumn();
					ImGui::Text("%s", GetCategoryAsString(entry.category).data());

					ImGui::TableNextColumn();
					ImGui::Text("%s", entry.message.data());
				}
			}

			ImGui::EndTable();
			ImGui::NewLine();
		}

		ImGui::End();
	}
}