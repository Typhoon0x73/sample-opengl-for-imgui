#ifndef MAINMENUBAR_H_
#define MAINMENUBAR_H_

#include "WidgetBase.h"

class MainMenuBar : public WidgetBase
{
public:
	explicit MainMenuBar();
	virtual ~MainMenuBar() = default;

	virtual void onRun() override;
};

#endif // !MAINMENUBAR_H_
