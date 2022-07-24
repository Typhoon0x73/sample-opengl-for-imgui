#include "MainMenuBar.h"
#include "../FileDialog.h"

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
			if (ImGui::MenuItem("open"))
			{
				std::wstring filter = L"スプライトアニメーションファイル(*.spa)\0*.spa\0全てのファイル(*.spa)\0*.*\0\0";
				std::wstring defext = L"*.spa";
				WCHAR path[PATH_MAX];
				bool isFileArray = false;
				if (FileDialog::Open(nullptr, FileDialog::Mode::Open, L"アニメーションファイルの読み込み", filter, defext, path, isFileArray))
				{

				}
			}

			if (ImGui::MenuItem("save"))
			{

			}

			if (ImGui::MenuItem("save as"))
			{

			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
