#include "WidgetManager.h"

WidgetManager::WidgetManager()
	: m_WidgetList{ 0 }
{
}

WidgetManager::~WidgetManager()
{
	m_WidgetList.clear();
}

void WidgetManager::regist(const WidgetPtr& widget)
{
	if (widget)
	{
		m_WidgetList.push_back(widget);
	}
}

void WidgetManager::update()
{
	for (const auto& it : m_WidgetList)
	{
		if (!it->isValidAnimakeData())
		{
			continue;
		}
		it->onRun();
	}
}
