#ifndef ANIMATIONVIEW_H_
#define ANIMATIONVIEW_H_

#include "WidgetBase.h"

class AnimationView : public WidgetBase
{
public:

	explicit AnimationView();
	virtual ~AnimationView() = default;

	virtual void onRun() override;
};

#endif // !ANIMATIONVIEW_H_
