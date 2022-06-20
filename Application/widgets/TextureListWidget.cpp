#include "TextureListWidget.h"

TextureListWidget::TextureListWidget()
	: WidgetBase()
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
	}
	ImGui::End();
}
