#include "TextureListWidget.h"
#include <filesystem>

TextureListWidget::TextureListWidget()
	: WidgetBase(eTaskPrio_TextureListWidget)
{
}

void TextureListWidget::onRun()
{
	auto& selectTextureNo  = m_pAnimakeData->m_SelectTextureNo;
	auto& texturePathArray = m_pAnimakeData->m_TexturePathArray;

	ImGui::Begin("textures");
	{
		if (ImGui::BeginListBox("##textureList"))
		{
			if (ImGui::Selectable("none", selectTextureNo == -1))
			{
				selectTextureNo = -1;
			}
			const auto& texCount = texturePathArray.size();
			for (std::size_t i = 0; i < texCount; i++)
			{
				if (ImGui::Selectable(texturePathArray[i].c_str(), i == selectTextureNo))
				{
					selectTextureNo = i;
					break;
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("add##texture_add"))
		{
			ImGui::OpenPopup("##load_texture_dialog");
		}
		if (ImGui::BeginPopup("##load_texture_dialog", ImGuiWindowFlags_Modal))
		{
			if (ImGui::Begin("load texture##load_texture_window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::Button("load"))
				{
					ImGui::CloseCurrentPopup();
				} ImGui::SameLine();
				if (ImGui::Button("cancel"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::End();
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}
