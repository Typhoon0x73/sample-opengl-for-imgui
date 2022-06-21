#include "MainToolBar.h"

MainToolBar::MainToolBar()
	: WidgetBase(eTaskPrio_ToolBar)
{
}

void MainToolBar::onRun()
{
	ImGui::Begin("tool bar");
	{

	}
	ImGui::End();
}
