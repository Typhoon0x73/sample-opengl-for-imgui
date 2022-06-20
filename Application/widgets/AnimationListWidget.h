#ifndef ANIMATIONLISTWIDGET_H_
#define ANIMATIONLISTWIDGET_H_

#include "WidgetBase.h"

class AnimationListWidget : public WidgetBase
{
public:

	explicit AnimationListWidget();
	virtual ~AnimationListWidget() = default;

	virtual void onRun() override;
};

#endif // !ANIMATIONLISTWIDGET_H_
