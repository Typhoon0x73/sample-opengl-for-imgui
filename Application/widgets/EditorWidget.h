#pragma once
#include "WidgetBase.h"
class EditorWidget : public WidgetBase
{
public:

	explicit EditorWidget();
	virtual ~EditorWidget() = default;

	virtual void onRun() override;
};

