#include "ErrorManager.h"

#include <stdio.h>
#include <stdarg.h>

#include "imgui/imgui.h"

namespace hk
{
	void ErrorManager::Error(ErrorCategory category, const char* message, ...)
	{
		char buffer[512];
		va_list args;
		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		auto [itr, did_insert] = m_errors.insert({ buffer, hk::ErrorInfo{ category, 1 } });
		if (did_insert == false)
		{
			itr->second.count++;
		}
	}

	void ErrorManager::AddToImGui()
	{
		ImGui::Begin("Error List");

        if (ImGui::BeginTable("Error List", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("Count");
            ImGui::TableSetupColumn("Message");
            ImGui::TableHeadersRow();

			for (const auto& [error_msg, error_info] : m_errors)
			{
				ImGui::TableNextRow();

				ImGui::TableNextColumn();
				ImGui::Text("%d", error_info.count);

				ImGui::TableNextColumn();
				ImGui::Text("%s", error_msg.data());
			}

            ImGui::EndTable();
        }

		ImGui::End();
	}
}