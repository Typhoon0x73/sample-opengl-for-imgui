#include "PatternListWidget.h"

PatternListWidget::PatternListWidget()
	: WidgetBase()
{
}

void PatternListWidget::onRun()
{
	const auto& editAnimNo         = m_pAnimakeData->m_EditAnimNo;
	auto&       editPatternNo      = m_pAnimakeData->m_EditPatternNo;
	auto&       editPatternLayerNo = m_pAnimakeData->m_EditPatternLayerNo;
	auto&       animation          = m_pAnimakeData->m_SpriteAnimation;
	const auto& sampleTextures     = m_pAnimakeData->m_SampleTextures;

	ImGui::Begin("patterns", nullptr, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		auto const anims = animation.animationArray();
		auto const ptns  = anims->at(editAnimNo).second.patternArray();
		if (!ptns)
		{

		}
		else
		{
			auto ptnCount = ptns->size();
			for (std::size_t i = 0; i < ptnCount; i++)
			{
				const auto& ptn = ptns->at(i);
				const auto& selectLayer = ptn.m_LayerArray[editPatternLayerNo].second;
				const auto& no = selectLayer.m_ImageNo;
				if (no < 0)
				{
					if (ImGui::Button("no image"))
					{
						editPatternNo = i;
						break;
					}
				}
				else
				{
					auto tex = sampleTextures[no];
					auto tw  = (float)tex->Width();
					auto th  = (float)tex->Height();
					ImVec2 uv0((float)selectLayer.m_OffsetX / tw, (float)selectLayer.m_OffsetY / th);
					ImVec2 uv1((float)(selectLayer.m_OffsetX + selectLayer.m_Width) / tw, (float)(selectLayer.m_OffsetY + selectLayer.m_Height) / th);
					ImTextureID id = (void*)tex->ID();
					auto w = (float)selectLayer.m_Width;
					auto h = (float)selectLayer.m_Height;
					ImVec2 padding = ImGui::GetStyle().FramePadding;
					ImVec4 bgColor = ((i == editPatternNo) ? ImGui::GetStyle().Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 });
					ImVec4 tintColor{ 1.0f, 1.0f, 1.0f, 1.0f };
					auto btnId = "##ptn_id_" + std::to_string(i);
					if (ImGui::ImageButtonEx(ImGui::GetID(btnId.c_str()), id, ImVec2(w, h), uv0, uv1, padding, bgColor, tintColor))
					{
						editPatternNo = i;
						break;
					}
				}
				ImGui::SameLine();
			}
		}
	}
	ImGui::End();
}
