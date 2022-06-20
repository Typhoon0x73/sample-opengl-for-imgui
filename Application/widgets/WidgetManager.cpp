#include "WidgetManager.h"

WidgetManager::WidgetManager()
	: m_WidgetList{ 0 }
{
}

WidgetManager::~WidgetManager()
{
	m_WidgetList.clear();
}

void WidgetManager::regist(WidgetPtr widget)
{
	if (widget)
	{
		m_WidgetList.push_back(widget);
	}
}

void WidgetManager::update()
{
	std::sort(
		m_WidgetList.begin(), m_WidgetList.end(),
		[](const auto& v1, const auto& v2) { return v1->getPrio() < v2->getPrio(); });
	for (const auto& it : m_WidgetList)
	{
		if (!it->isValidAnimakeData())
		{
			continue;
		}
		it->onRun();
	}
}
