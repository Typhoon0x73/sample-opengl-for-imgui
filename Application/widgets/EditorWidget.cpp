#include "EditorWidget.h"

EditorWidget::EditorWidget()
	: WidgetBase(eTaskPrio_EditWidget)
	, m_PatternCount(0)
{
	std::fill_n(m_LayerName, 128, 0);
}

void EditorWidget::onRun()
{
	const auto& editAnimNo         = m_pAnimakeData->m_EditAnimNo;
	const auto& editPatternNo      = m_pAnimakeData->m_EditPatternNo;
	auto&       editPatternLayerNo = m_pAnimakeData->m_EditPatternLayerNo;
	auto&       animation          = m_pAnimakeData->m_SpriteAnimation;
	const auto& texturePathArray   = m_pAnimakeData->m_TexturePathArray;

	ImGui::Begin("editor");
	{
		auto const pattern = animation.animationArray()->at(editAnimNo).second.patternByArrayNo(editPatternNo);
		if (!pattern)
		{
			ImGui::LabelText("##editor_please_create_pattern.", "please create pattern.");

			if (ImGui::Button("create##pattern_create"))
			{
				ImGui::OpenPopup("create patterns");
			}

			if (ImGui::BeginPopupModal("create patterns", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				int patternCount = static_cast<int>(m_PatternCount);
				if (ImGui::DragInt("pattern count", &patternCount, 1.0f, 0, INT32_MAX))
				{
					m_PatternCount = static_cast<std::size_t>(patternCount);
				}
				if (ImGui::Button("create##create_patterns"))
				{
					for (std::size_t i = 0; i < m_PatternCount; i++)
					{
						auto pAnim = &(animation.animationByArrayNo(editAnimNo)->second);
						pAnim->addPattern(std::move(spa::Pattern({ spa::LayerData{ "layer_0", spa::Layer() } }, 0.000)));
					}
					resetInputText();
					ImGui::CloseCurrentPopup();
				} ImGui::SameLine();
				if (ImGui::Button("cancel##create_patterns"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			ImGui::End();
			refreshPrevNo();
			return;
		}

		if (changedEditAnimNo() || changedEditPatternNo())
		{
			editPatternLayerNo = 0;
			resetInputText();
		}
		if (m_LayerName[0] == 0)
		{
			resetInputText();
		}
		if (ImGui::InputText("layer name", m_LayerName, IM_ARRAYSIZE(m_LayerName), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string str = m_LayerName;
			if (str.length() > 0)
			{
				pattern->m_LayerArray[editPatternLayerNo].first = str;
			}
		}
		if (ImGui::BeginListBox("Layers", ImVec2(0.0f, 3.0f * 18.0f)))
		{
			const auto& layerCount = pattern->m_LayerArray.size();
			for (std::size_t i = 0; i < layerCount; i++)
			{
				const auto& layer     = pattern->m_LayerArray[i];
				const auto  layer_tmp = layer;
				if (ImGui::Selectable(layer.first.c_str(), (i == editPatternLayerNo)))
				{
					editPatternLayerNo = i;
					resetInputText();
					break;
				}
				if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
				{
					int i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
					if (i_next >= 0 && i_next < layerCount)
					{
						pattern->m_LayerArray[i]      = pattern->m_LayerArray[i_next];
						pattern->m_LayerArray[i_next] = layer_tmp;
						ImGui::ResetMouseDragDelta();
					}
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("add##add_layer"))
		{
			std::int32_t n = 0;
			const auto& layerCount = pattern->m_LayerArray.size();
			std::string layerName  = "layer_" + std::to_string(n);
			for (std::size_t i = 0; i < layerCount;)
			{
				if (layerName.compare(pattern->m_LayerArray.at(i).first) == 0)
				{
					layerName = "layer_" + std::to_string(++n);
					i         = 0;
					continue;
				}
				i++;
			}
			pattern->m_LayerArray.push_back(spa::LayerData(layerName, spa::Layer(-1, 0, 0, 0, 0, 0, 0)));
		} ImGui::SameLine();
		if (ImGui::Button("delete##delete_layer"))
		{
			if (pattern->m_LayerArray.size() <= 1)
			{
				ImGui::OpenPopup("not delete item");
			}
			else
			{
				pattern->m_LayerArray.erase(pattern->m_LayerArray.begin() + editPatternLayerNo);
				editPatternLayerNo = std::clamp(editPatternLayerNo, 0, static_cast<std::int32_t>(pattern->m_LayerArray.size() - 1));
				resetInputText();
			}
		}

		if (ImGui::BeginPopupModal("not delete item", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::LabelText("##can't_delete...", "can't delete...");
			if (ImGui::Button("hmm..."))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		auto const  selectLayer = &(pattern->m_LayerArray[editPatternLayerNo].second);
		const auto& imageNo     = selectLayer->m_ImageNo;
		bool        isValid     = (imageNo >= 0) && (imageNo < (std::int32_t)texturePathArray.size());
		const char* selectName  = (isValid ? texturePathArray[imageNo].c_str() : "none");
		if (ImGui::BeginCombo("texture", selectName))
		{
			if (ImGui::Selectable("none", (imageNo == -1)))
			{
				selectLayer->m_ImageNo = -1;
			}
			auto texPathCount = texturePathArray.size();
			for (std::size_t i = 0; i < texPathCount; i++)
			{
				if (ImGui::Selectable(texturePathArray[i].c_str(), (i == imageNo)))
				{
					selectLayer->m_ImageNo = i;
				}
			}
			ImGui::EndCombo();
		}
		auto offsetX = selectLayer->m_OffsetX;
		if (ImGui::DragInt("offset x", &offsetX))
		{
			selectLayer->m_OffsetX = offsetX;
		}
		auto offsetY = selectLayer->m_OffsetY;
		if (ImGui::DragInt("offset y", &offsetY))
		{
			selectLayer->m_OffsetY = offsetY;
		}
		auto width = selectLayer->m_Width;
		if (ImGui::DragInt("width", &width))
		{
			selectLayer->m_Width = width;
		}
		auto height = selectLayer->m_Height;
		if (ImGui::DragInt("height", &height))
		{
			selectLayer->m_Height = height;
		}
		auto drawOffsetX = selectLayer->m_DrawOffsetX;
		if (ImGui::DragInt("draw offset x", &drawOffsetX))
		{
			selectLayer->m_DrawOffsetX = drawOffsetX;
		}
		auto drawOffsetY = selectLayer->m_DrawOffsetY;
		if (ImGui::DragInt("draw offset y", &drawOffsetY))
		{
			selectLayer->m_DrawOffsetY = drawOffsetY;
		}
		float refresh = static_cast<float>(pattern->m_RefreshTime);
		if (ImGui::DragFloat("refresh", &refresh, 0.004f, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
		{
			pattern->m_RefreshTime = static_cast<double>(refresh);
		}
	}
	ImGui::End();
	refreshPrevNo();
}

void EditorWidget::resetInputText()
{
	const auto& editAnimNo         = m_pAnimakeData->m_EditAnimNo;
	const auto& editPatternNo      = m_pAnimakeData->m_EditPatternNo;
	auto&       editPatternLayerNo = m_pAnimakeData->m_EditPatternLayerNo;
	auto&       animation          = m_pAnimakeData->m_SpriteAnimation;
	auto const  pAnimArray         = animation.animationArray();
	std::fill_n(m_LayerName, 128, 0);
	if (!pAnimArray)
	{
		return;
	}
	auto const pPattern = pAnimArray->at(editAnimNo).second.patternByArrayNo(editPatternNo);
	if (!pPattern)
	{
		std::fill_n(m_LayerName, 128, 0);
		return;
	}
	const auto& layerName = pPattern->m_LayerArray[editPatternLayerNo].first;
	std::copy(layerName.begin(), layerName.end(), m_LayerName);
}
