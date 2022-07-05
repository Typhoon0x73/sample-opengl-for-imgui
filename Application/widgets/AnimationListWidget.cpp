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
		auto pAnimArray = animation.animationArray();

		if (changedEditAnimNo() || m_AnimationName[0] == 0)
		{
			resetInputText();
		}
		if (ImGui::InputText("animation name", m_AnimationName, IM_ARRAYSIZE(m_AnimationName), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string str = m_AnimationName;
			if (str.length() > 0)
			{
				animation.animationByArrayNo(editAnimNo)->first = str;
			}
		}

		if (ImGui::BeginListBox("##animationList"))
		{
			auto listCount = pAnimArray->size();
			for (std::size_t i = 0; i < listCount; i++)
			{
				auto anim = pAnimArray->at(i);
				if (ImGui::Selectable(anim.first.c_str(), (i == editAnimNo)))
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
		if (ImGui::Button("duplicate##duplicate_animation"))
		{
			const auto& animCount = pAnimArray->size();
			std::string animName  = pAnimArray->at(editAnimNo).first + "_copy";
			for (std::size_t i = 0; i < animCount;)
			{
				if (animName.compare(pAnimArray->at(i).first) == 0)
				{
					animName += "_copy";
					i = 0;
					continue;
				}
				i++;
			}
			pAnimArray->insert(pAnimArray->begin() + editAnimNo + 1, spa::AnimationData(animName, pAnimArray->at(editAnimNo).second));
		} ImGui::SameLine();
		if (ImGui::Button("add##add_animation"))
		{
			std::int32_t n = 0;
			const auto& animCount = pAnimArray->size();
			std::string animName  = "animation_" + std::to_string(n);
			for (std::size_t i = 0; i < animCount;)
			{
				if (animName.compare(pAnimArray->at(i).first) == 0)
				{
					animName = "animation_" + std::to_string(++n);
					i         = 0;
					continue;
				}
				i++;
			}
			pAnimArray->push_back(spa::AnimationData(animName, spa::SpriteAnimation()));
		} ImGui::SameLine();
		if (ImGui::Button("erase##erase_animation"))
		{
			if (pAnimArray->size() > 1)
			{
				pAnimArray->erase(pAnimArray->begin() + editAnimNo);
				editAnimNo = std::clamp(editAnimNo, 0, static_cast<std::int32_t>(pAnimArray->size()) - 1);
				animation.changeAnimation(editAnimNo);
			}
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