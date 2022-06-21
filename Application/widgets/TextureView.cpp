#include "TextureView.h"

TextureView::TextureView()
	: WidgetBase(eTaskPrio_ViewWidget)
{
}

void TextureView::onRun()
{
	const auto& selectTextureNo = m_pAnimakeData->m_SelectTextureNo;
	const auto& sampleTextures  = m_pAnimakeData->m_SampleTextures;

	ImGui::Begin("texture view", nullptr, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	{
		if (selectTextureNo < 0)
		{
			ImGui::LabelText("##please select texture.", "please select texture.");
		}
		else
		{
			const auto&  tex = sampleTextures[selectTextureNo];
			const ImVec2 size((float)tex->Width(), (float)tex->Height());
			ImGui::Image((ImTextureID)tex->ID(), size);
		}
	}
	ImGui::End();
}
