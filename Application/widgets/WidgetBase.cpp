#include "WidgetBase.h"
#include "WidgetManager.h"
#include "../Blackboard/SingletonBlackboard.h"

WidgetBase::WidgetBase()
	: m_pAnimakeData{ nullptr }
{
	m_pAnimakeData = g_pGetBlackboard(AnimakeDataPtr&)->get("AnimakeData");
}

bool WidgetBase::isValidAnimakeData() const
{
	return (m_pAnimakeData != nullptr);
}
