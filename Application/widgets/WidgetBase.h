#ifndef WIDGETBASE_H_
#define WIDGETBASE_H_

#include    "imgui.h"
#include    "imgui_internal.h"
#include    "../../AnimakeData.h"

enum TaskPrio
{
	eTaskPrio_MenuBar,
	eTaskPrio_ToolBar,
	eTaskPrio_UtilWidget,
	eTaskPrio_TextureListWidget,
	eTaskPrio_AnimationListWidget,
	eTaskPrio_PatternListWidget,
	eTaskPrio_CanvasWidget,
	eTaskPrio_EditWidget,

	eTaskPrio_ViewWidget,

	eTaskPrio_Unknown,
};

class WidgetBase
{
public:
	
	explicit WidgetBase(TaskPrio prio);
	virtual ~WidgetBase() = default;

	virtual void onRun() = 0;
  
	TaskPrio getPrio() const;

	bool isValidAnimakeData() const;

protected:

	void refreshPrevNo();

	bool changedEditAnimNo() const;
	bool changedEditPatternNo() const;
	bool changedEditPatternLayerNo() const;
	bool changedSelectTextureNo() const;

	AnimakeDataPtr m_pAnimakeData{ nullptr };
  
private:

	TaskPrio m_TaskPrio{ eTaskPrio_Unknown };
	int      m_PrevEditAnimNo{ 0 };
	int      m_PrevEditPatternNo{ 0 };
	int      m_PrevEditPatternLayerNo{ 0 };
	int      m_PrevSelectTextureNo{ -1 };
};

using WidgetPtr = std::unique_ptr<WidgetBase>;

#endif // !WIDGETBASE_H_
