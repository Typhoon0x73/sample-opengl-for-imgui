#ifndef MAINTOOLBAR_H_
#define MAINTOOLBAR_H_

#include "WidgetBase.h"

class MainToolBar : public WidgetBase
{
public:

	explicit MainToolBar();
	virtual ~MainToolBar() = default;

	virtual void onRun() override;
};

#endif // !MAINTOOLBAR_H_
