#ifndef WIDGETMANAGER_H_
#define WIDGETMANAGER_H_

#include "WidgetBase.h"
#include "../../Framework/Common/Singleton.h"
#include <vector>

class WidgetManager : public Sample::Singleton<WidgetManager>
{
	friend class Sample::Singleton<WidgetManager>;

public:
	explicit WidgetManager();
	virtual ~WidgetManager();

	void regist(WidgetPtr widget);

	void update();

private:

	std::vector<WidgetPtr> m_WidgetList;
};

#endif // !WIDGETMANAGER_H_


