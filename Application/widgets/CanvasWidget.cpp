#include "CanvasWidget.h"
#include "../../PrimitiveRenderUtilities.h"

CanvasWidget::CanvasWidget()
	: WidgetBase(eTaskPrio_CanvasWidget)
{
}

void CanvasWidget::onRun()
{
	const auto& sampleTextures = m_pAnimakeData->m_SampleTextures;
	const auto& animation      = m_pAnimakeData->m_SpriteAnimation;

	ImGui::Begin("canvas", nullptr, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		auto tex = sampleTextures[0];
		ImVec2 size((float)tex->Width(), (float)tex->Height());
		ImGui::Image((ImTextureID)tex->ID(), size);
		ImGui::SameLine();
		auto ptn = animation.currentPattern();
		if (ptn)
		{
			for (const auto& layer : ptn->m_LayerArray)
			{
				const auto& scrollX = ImGui::GetScrollX();
				const auto& scrollY = ImGui::GetScrollY();
				const auto& padding = ImGui::GetStyle().WindowPadding;
				const auto& pos     = ImGui::GetWindowPos();
				const auto& t       = ImGui::GetCurrentContext()->CurrentWindow->TitleBarHeight();
				const auto& x       = layer.second.m_OffsetX + pos.x + padding.x - scrollX;
				const auto& y       = layer.second.m_OffsetY + pos.y + padding.y - scrollY + t;
				const auto& w       = (float)layer.second.m_Width;
				const auto& h       = (float)layer.second.m_Height;
				PrimitiveRenderUtilities::RenderRect(x, y, w, h, { 0.6f, 0.1f, 0.1f, 1.0f }, false);
			}
		}
	}
	ImGui::End();
}
