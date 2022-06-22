#include "WidgetBase.h"
#include "WidgetManager.h"
#include "../Blackboard/SingletonBlackboard.h"

WidgetBase::WidgetBase(TaskPrio prio)
	: m_pAnimakeData{ nullptr }
	, m_TaskPrio{ prio }
	, m_PrevEditAnimNo{ 0 }
	, m_PrevEditPatternNo{ 0 }
	, m_PrevEditPatternLayerNo{ 0 }
	, m_PrevSelectTextureNo{ -1 }
{
	m_pAnimakeData = g_pGetBlackboard(AnimakeDataPtr&)->get("AnimakeData");
}

TaskPrio WidgetBase::getPrio() const
{
	return m_TaskPrio;
}

bool WidgetBase::isValidAnimakeData() const
{
	return (m_pAnimakeData != nullptr);
}

void WidgetBase::refreshPrevNo()
{
	m_PrevEditAnimNo         = m_pAnimakeData->m_EditAnimNo;
	m_PrevEditPatternNo      = m_pAnimakeData->m_EditPatternNo;
	m_PrevEditPatternLayerNo = m_pAnimakeData->m_EditPatternLayerNo;
	m_PrevSelectTextureNo    = m_pAnimakeData->m_SelectTextureNo;
}

bool WidgetBase::changedEditAnimNo() const
{
	return (m_pAnimakeData->m_EditAnimNo != m_PrevEditAnimNo);
}

bool WidgetBase::changedEditPatternNo() const
{
	return (m_pAnimakeData->m_EditPatternNo != m_PrevEditPatternNo);
}

bool WidgetBase::changedEditPatternLayerNo() const
{
	return (m_pAnimakeData->m_EditPatternLayerNo != m_PrevEditPatternLayerNo);
}

bool WidgetBase::changedSelectTextureNo() const
{
	return (m_pAnimakeData->m_SelectTextureNo != m_PrevSelectTextureNo);
}
