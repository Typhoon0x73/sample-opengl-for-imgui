#include "MainMenuBar.h"

MainMenuBar::MainMenuBar()
	: WidgetBase(eTaskPrio_MenuBar)
{
}

void MainMenuBar::onRun()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("file"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
