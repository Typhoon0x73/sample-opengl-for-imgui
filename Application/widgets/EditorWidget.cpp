#include "EditorWidget.h"

EditorWidget::EditorWidget()
	: WidgetBase(eTaskPrio_EditWidget)
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
			ImGui::LabelText("##editor_please_add_pattern.", "please add pattern.");
			ImGui::End();
			refreshPrevNo();
			return;
		}

		if (changedEditPatternNo())
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
				const auto& layer = pattern->m_LayerArray[i];
				if (ImGui::Selectable(layer.first.c_str(), (i == editPatternLayerNo)))
				{
					editPatternLayerNo = i;
					resetInputText();
					break;
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("add##add_layer"))
		{
			std::int32_t n = 0;
			const auto& layerCount = pattern->m_LayerArray.size();
			std::string layerName  = "layer_" + std::to_string(n);
			for (std::size_t i = 0; i < layerCount; i++)
			{
				if (layerName.compare(pattern->m_LayerArray.at(i).first) == 0)
				{
					layerName = "layer_" + std::to_string(++n);
					i         = 0;
					continue;
				}
			}
			pattern->m_LayerArray.push_back(spa::LayerData(layerName, spa::Layer(-1, 0, 0, 0, 0, 0, 0)));
		} ImGui::SameLine();
		if (ImGui::Button("delete##delete_layer"))
		{

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
	if (!pAnimArray)
	{
		std::fill_n(m_LayerName, 128, 0);
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
