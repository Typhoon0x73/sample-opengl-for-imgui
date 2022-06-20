#include "AnimationListWidget.h"

AnimationListWidget::AnimationListWidget()
	: WidgetBase(eTaskPrio_AnimationListWidget)
{
}

void AnimationListWidget::onRun()
{
	auto& editAnimNo = m_pAnimakeData->m_EditAnimNo;
	auto& animation  = m_pAnimakeData->m_SpriteAnimation;

	ImGui::Begin("animations");
	{
		int current = editAnimNo;
		auto pAnimArray = animation.animationArray();
		if (ImGui::BeginListBox("##animationList"))
		{
			if (pAnimArray)
			{
				auto listCount = pAnimArray->size();
				for (std::size_t i = 0; i < listCount; i++)
				{
					auto anim = pAnimArray->at(i);
					if (ImGui::Selectable(anim.first.c_str(), (i == current)))
					{
						animation.changeAnimation(i);
						editAnimNo = i;
					}
				}
			}
			else
			{

			}
			ImGui::EndListBox();
		}
	}
	ImGui::End();
}
