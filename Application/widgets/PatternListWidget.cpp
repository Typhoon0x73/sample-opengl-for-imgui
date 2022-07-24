#include "PatternListWidget.h"

PatternListWidget::PatternListWidget()
	: WidgetBase(eTaskPrio_PatternListWidget)
	, m_ChildSize(0, 0)
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
			if (ImGui::BeginChild("patterns##patterns_child", m_ChildSize, true))
			{
				auto childSizeH = m_ChildSize.y;
				auto ptnCount   = ptns->size();
				for (std::size_t i = 0; i < ptnCount; i++)
				{
					auto maxW = 0.0f;
					auto maxH = 0.0f;
					const auto& ptn = ptns->at(i);
					const auto& layerCount = ptn.m_LayerArray.size();
					bool isValidImages = false;
					for (std::size_t j = 0; j < layerCount; j++)
					{
						auto& layerData = ptn.m_LayerArray[j].second;
						const auto& no = layerData.m_ImageNo;
						if (no < 0)
						{
							continue;
						}
						isValidImages = true;
						auto w = (float)layerData.m_Width + layerData.m_DrawOffsetX;
						auto h = (float)layerData.m_Height + layerData.m_DrawOffsetY;
						if (maxW < w) { maxW = w; }
						if (maxH < h) { maxH = h; }
					}
					childSizeH    = maxH;
					ImVec2 btnPos = ImGui::GetCurrentWindow()->DC.CursorPos;
					if (ImGui::Button(std::string("pattern" + std::to_string(i)).c_str(), ImVec2(maxW, maxH)))
					{
						editPatternNo = i;
						break;
					}
					if (isValidImages)
					{
						for (std::size_t j = 0; j < layerCount; j++)
						{
							auto window = ImGui::GetCurrentWindow();
							if (window->SkipItems)
							{
								continue;
							}
							auto& layerData = ptn.m_LayerArray[j].second;
							const auto& no = layerData.m_ImageNo;
							if (no < 0 || sampleTextures.size() <= no)
							{
								continue;
							}
							isValidImages = true;
							auto tex = sampleTextures[no];
							auto tw = (float)tex->Width();
							auto th = (float)tex->Height();
							ImVec2 uv0((float)layerData.m_OffsetX / tw, (float)layerData.m_OffsetY / th);
							ImVec2 uv1((float)(layerData.m_OffsetX + layerData.m_Width) / tw, (float)(layerData.m_OffsetY + layerData.m_Height) / th);
							ImTextureID id = (void*)tex->ID();
							auto w = (float)layerData.m_Width;
							auto h = (float)layerData.m_Height;
							ImVec2 padding = ImGui::GetStyle().FramePadding;
							ImVec4 bgColor = ((i == editPatternNo) ? ImGui::GetStyle().Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 });
							ImVec4 tintColor{ 1.0f, 1.0f, 1.0f, 1.0f };
							btnPos.x += layerData.m_DrawOffsetX;
							btnPos.y += layerData.m_DrawOffsetY;
							const auto& bbMax = ImVec2(btnPos.x + w, btnPos.y + h);
							ImRect bb(btnPos, bbMax);
							if (!ImGui::ItemAdd(bb, 0)) continue;
							window->DrawList->AddImage((ImTextureID)tex->ID(), bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(tintColor));
						}
					}
					ImGui::SameLine();
				}
				if (ptnCount == 0)
				{
					childSizeH = 0;
				}
				m_ChildSize.y = childSizeH + ImGui::GetStyle().WindowPadding.y * 2.0f;
				ImGui::EndChild();
			}
		}
		if (ImGui::Button("duplicate##duplicate_patterns"))
		{

		} ImGui::SameLine();
		if (ImGui::Button("add##add_patterns"))
		{

		} ImGui::SameLine();
		if (ImGui::Button("erase##erase_patterns"))
		{

		}
	}
	ImGui::End();
}
