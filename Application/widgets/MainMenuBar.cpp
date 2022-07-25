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
				std::wstring_view filter = L"スプライトアニメーションファイル(*.spa)\0*.spa\0All(*.*)\0*.*\0\0";
				std::wstring_view defext = L"spa";
				WCHAR path[PATH_MAX];
				bool isFileArray = false;
				if (FileDialog::Open(nullptr, FileDialog::Mode::Open, L"アニメーションファイルの読み込み", filter, defext, path, isFileArray))
				{
					std::string spa_file = wide_to_sjis(path);
					if (isFileArray)
					{
						std::vector<std::wstring> pathArray;
						std::wstring currentPath;
						FileDialog::SeparatePath(path, pathArray, &currentPath);
						spa_file = wide_to_sjis(currentPath + L"\\" + pathArray[0]);
					}
					spa::SpriteAnimationDataParser parser(spa_file.c_str());
					parser.parseFromSPA(&m_pAnimakeData->m_SpriteAnimation, &m_pAnimakeData->m_TexturePathArray);
					m_pAnimakeData->m_OpenFileName = spa_file;
					m_pAnimakeData->m_SampleTextures.clear();
					for (const auto& texture_path : m_pAnimakeData->m_TexturePathArray)
					{
						m_pAnimakeData->m_SampleTextures.push_back(std::make_shared<Sample::Texture>(texture_path.c_str()));
					}
				}
			}

			if (ImGui::MenuItem("save"))
			{
				if (m_pAnimakeData->m_OpenFileName.length() > 4)
				{
					spa::SpriteAnimationDataExporter exporter(m_pAnimakeData->m_OpenFileName.c_str());
					exporter.exportToSPA(&m_pAnimakeData->m_SpriteAnimation, &m_pAnimakeData->m_TexturePathArray);
				}
			}

			if (ImGui::MenuItem("save as"))
			{
				std::wstring_view filter = L"スプライトアニメーションファイル(*.spa)\0*.spa\0All(*.*)\0*.*\0\0";
				std::wstring_view defext = L"spa";
				WCHAR path[PATH_MAX];
				bool isFileArray = false;
				if (FileDialog::Open(nullptr, FileDialog::Mode::Save, L"アニメーションファイルの保存", filter, defext, path, isFileArray))
				{
					std::string spa_file = wide_to_sjis(path);
					spa::SpriteAnimationDataExporter exporter(spa_file.c_str());
					exporter.exportToSPA(&m_pAnimakeData->m_SpriteAnimation, &m_pAnimakeData->m_TexturePathArray);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}
