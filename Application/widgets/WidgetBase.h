#ifndef WIDGETBASE_H_
#define WIDGETBASE_H_

#include    "imgui.h"
#include    "imgui_internal.h"
#include    "../../AnimakeData.h"

class WidgetBase
{
public:
	
	explicit WidgetBase();
	virtual ~WidgetBase() = default;

	virtual void onRun() = 0;

	bool isValidAnimakeData() const;

protected:

	AnimakeData* m_pAnimakeData{ nullptr };
};

using WidgetPtr = std::unique_ptr<WidgetBase>;

#endif // !WIDGETBASE_H_
