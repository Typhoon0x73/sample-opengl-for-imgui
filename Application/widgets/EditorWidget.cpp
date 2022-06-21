#include "EditorWidget.h"

EditorWidget::EditorWidget()
	: WidgetBase()
{
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

		}
		else
		{
			if (ImGui::BeginListBox("Layers"))
			{
				const auto& layerCount = pattern->m_LayerArray.size();
				for (std::size_t i = 0; i < layerCount; i++)
				{
					const auto& layer = pattern->m_LayerArray[i];
					if (ImGui::Selectable(layer.first.c_str(), (i == editPatternLayerNo)))
					{
						editPatternLayerNo = i;
						break;
					}
				}
				ImGui::EndListBox();
			}
			auto selectLayer = &(pattern->m_LayerArray[editPatternLayerNo].second);
			const auto& imageNo = selectLayer->m_ImageNo;
			bool isValid = (imageNo >= 0) && (imageNo < (std::int32_t)texturePathArray.size());
			const char* const selectName = (isValid ? texturePathArray[imageNo].c_str() : "none");
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
	}
	ImGui::End();
}
