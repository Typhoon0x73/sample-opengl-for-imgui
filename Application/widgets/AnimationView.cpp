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
			for (const auto& layer : ptn->m_LayerArray)
			{
				const auto& imageNo = layer.second.m_ImageNo;
				if (imageNo < 0)
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
				ImGui::Image((ImTextureID)tex->ID(), ImVec2((float)w, (float)h), uv0, uv1);
			}
		}
	}
	ImGui::End();
}
