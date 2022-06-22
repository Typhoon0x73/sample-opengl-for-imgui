#include "AnimationView.h"

AnimationView::AnimationView()
	: WidgetBase(eTaskPrio_ViewWidget)
{
}

void AnimationView::onRun()
{
	const auto& animation      = m_pAnimakeData->m_SpriteAnimation;
	const auto& sampleTextures = m_pAnimakeData->m_SampleTextures;

	ImGui::Begin("animation view");
	{
		auto ptn = animation.currentPattern();
		if (ptn)
		{
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			ImVec2 animPos = window->DC.CursorPos;
			for (const auto& layer : ptn->m_LayerArray)
			{
				const auto& imageNo = layer.second.m_ImageNo;
				if (imageNo < 0 || window->SkipItems)
				{
					continue;
				}
				const auto& x   = layer.second.m_OffsetX;
				const auto& y   = layer.second.m_OffsetY;
				const auto& w   = layer.second.m_Width;
				const auto& h   = layer.second.m_Height;
				const auto& tex = sampleTextures[imageNo];
				ImVec2 size((float)tex->Width(), (float)tex->Height());
				ImVec2 uv0((float)(x) / (float)tex->Width(), (float)(y) / (float)tex->Height());
				ImVec2 uv1((float)(x + w) / (float)tex->Width(), (float)(y + h) / (float)tex->Height());

				animPos.x += layer.second.m_DrawOffsetX;
				animPos.y += layer.second.m_DrawOffsetY;
				ImRect bb(animPos, ImVec2(animPos.x + w, animPos.y + h));
				if (!ImGui::ItemAdd(bb, 0))
					continue;
				window->DrawList->AddImage((ImTextureID)tex->ID(), bb.Min, bb.Max, uv0, uv1, ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));
			}
		}
	}
	ImGui::End();
}
