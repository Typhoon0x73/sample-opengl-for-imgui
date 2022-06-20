#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_

#include "WidgetBase.h"

class CanvasWidget : public WidgetBase
{
public:

	explicit CanvasWidget();
	virtual ~CanvasWidget() = default;

	virtual void onRun() override;
};

#endif // !CANVASWIDGET_H_
