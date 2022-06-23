#ifndef EDITORWIDGET_H_
#define EDITORWIDGET_H_

#include "WidgetBase.h"

class EditorWidget : public WidgetBase
{
public:

	explicit EditorWidget();
	virtual ~EditorWidget() = default;

	virtual void onRun() override;

	void resetInputText();
private:

	void initPatternCreatePopup();

	char m_LayerName[128];
	std::size_t m_PatternCount;
};

#endif // !EDITORWIDGET_H_
