#include "WidgetManager.h"

WidgetManager::WidgetManager()
	: m_pWidgetList{ nullptr }
{
	m_pWidgetList = new std::list<WidgetPtr>();
}

WidgetManager::~WidgetManager()
{
	m_pWidgetList->clear();
	if (m_pWidgetList)
	{
		delete m_pWidgetList;
		m_pWidgetList = nullptr;
	}
}

void WidgetManager::regist(WidgetPtr&& widget)
{
	if (widget)
	{
		m_pWidgetList->push_back(std::move(widget));
	}
}

void WidgetManager::update()
{
	for (const auto& it : (*m_pWidgetList))
	{
		if (!it->isValidAnimakeData())
		{
			continue;
		}
		it->onRun();
	}
}
