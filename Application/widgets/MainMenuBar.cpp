#include "MainMenuBar.h"

MainMenuBar::MainMenuBar()
	: WidgetBase()
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
