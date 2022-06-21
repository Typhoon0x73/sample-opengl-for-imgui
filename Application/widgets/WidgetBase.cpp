#include "WidgetBase.h"
#include "WidgetManager.h"
#include "../Blackboard/SingletonBlackboard.h"

WidgetBase::WidgetBase(TaskPrio prio)
	: m_TaskPrio{ prio }
	, m_pAnimakeData{ nullptr }
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
