#ifndef EDITORWIDGET_H_
#define EDITORWIDGET_H_

#include "WidgetBase.h"

class EditorWidget : public WidgetBase
{
public:

	explicit EditorWidget();
	virtual ~EditorWidget() = default;

	virtual void onRun() override;

private:

	char m_LayerName[128];
};

#endif // !EDITORWIDGET_H_
