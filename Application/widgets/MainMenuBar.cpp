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
				std::wstring filter = L"�X�v���C�g�A�j���[�V�����t�@�C��(*.spa)\0*.spa\0�S�Ẵt�@�C��(*.spa)\0*.*\0\0";
				std::wstring defext = L"*.spa";
				WCHAR path[PATH_MAX];
				bool isFileArray = false;
				if (FileDialog::Open(nullptr, FileDialog::Mode::Open, L"�A�j���[�V�����t�@�C���̓ǂݍ���", filter, defext, path, isFileArray))
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
