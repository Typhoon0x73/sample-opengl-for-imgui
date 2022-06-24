#include "AnimationListWidget.h"

AnimationListWidget::AnimationListWidget()
	: WidgetBase(eTaskPrio_AnimationListWidget)
{
}

void AnimationListWidget::onRun()
{
	auto& editAnimNo = m_pAnimakeData->m_EditAnimNo;
	auto& editPatternNo = m_pAnimakeData->m_EditPatternNo;
	auto& editPatternLayerNo = m_pAnimakeData->m_EditPatternLayerNo;
	auto& animation  = m_pAnimakeData->m_SpriteAnimation;

	ImGui::Begin("animations");
	{
		int current = editAnimNo;
		auto pAnimArray = animation.animationArray();

		if (changedEditAnimNo() || m_AnimationName[0] == 0)
		{
			resetInputText();
		}
		if (ImGui::InputText("layer name", m_AnimationName, IM_ARRAYSIZE(m_AnimationName), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string str = m_AnimationName;
			if (str.length() > 0)
			{
				animation.animationByArrayNo(current)->first = str;
			}
		}

		if (ImGui::BeginListBox("##animationList"))
		{
			auto listCount = pAnimArray->size();
			for (std::size_t i = 0; i < listCount; i++)
			{
				auto anim = pAnimArray->at(i);
				if (ImGui::Selectable(anim.first.c_str(), (i == current)))
				{
					animation.changeAnimation(i);
					editAnimNo = i;
					editPatternNo = 0;
					editPatternLayerNo = 0;
					break;
				}
				if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
				{
					int i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
					if (i_next >= 0 && i_next < listCount)
					{
						const auto tmp = animation.animationArray()->at(i);
						animation.animationArray()->at(i) = animation.animationArray()->at(i_next);
						animation.animationArray()->at(i_next) = tmp;
						ImGui::ResetMouseDragDelta();
					}
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("add##add_animation"))
		{
			
		} ImGui::SameLine();
		if (ImGui::Button("erase##erase_animation"))
		{

		}
	}
	ImGui::End();
}

void AnimationListWidget::resetInputText()
{
	const auto& editAnimNo = m_pAnimakeData->m_EditAnimNo;
	const auto& animation  = m_pAnimakeData->m_SpriteAnimation;
	const auto& pAnimArray = animation.animationArray();
	std::fill_n(m_AnimationName, 128, 0);
	if (!pAnimArray)
	{
		return;
	}
	auto const name = pAnimArray->at(editAnimNo).first;
	std::copy(name.begin(), name.end(), m_AnimationName);
}