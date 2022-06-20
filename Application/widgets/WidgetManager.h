#ifndef WIDGETMANAGER_H_
#define WIDGETMANAGER_H_

#include "WidgetBase.h"
#include "../../Framework/Common/Singleton.h"
#include <list>

class WidgetManager : public Sample::Singleton<WidgetManager>
{
	friend class Sample::Singleton<WidgetManager>;

public:
	explicit WidgetManager();
	virtual ~WidgetManager();

	void regist(WidgetPtr&& widget);

	void update();

private:

	std::list<WidgetPtr>* m_pWidgetList;
};

#endif // !WIDGETMANAGER_H_


