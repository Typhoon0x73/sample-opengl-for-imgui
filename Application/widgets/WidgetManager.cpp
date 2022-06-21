#include "WidgetManager.h"

WidgetManager::WidgetManager()
	: m_WidgetList{}
{
}

WidgetManager::~WidgetManager()
{
	m_WidgetList.clear();
}

void WidgetManager::regist(WidgetPtr&& widget)
{
	if (widget)
	{
		m_WidgetList.push_back(std::move(widget));
	}
}

void WidgetManager::update()
{
	m_WidgetList.sort([](const auto& v1, const auto& v2) { return v1->getPrio() < v2->getPrio(); });
	for (const auto& it : m_WidgetList)
	{
		if (!it->isValidAnimakeData())
		{
			continue;
		}
		it->onRun();
	}
}
