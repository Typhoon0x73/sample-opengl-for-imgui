#ifndef PATTERNLISTWIDGET_H_
#define PATTERNLISTWIDGET_H_

#include "WidgetBase.h"

class PatternListWidget : public WidgetBase
{
public:

	explicit PatternListWidget();
	virtual ~PatternListWidget() = default;

	virtual void onRun() override;
};

#endif // !PATTERNLISTWIDGET_H_
