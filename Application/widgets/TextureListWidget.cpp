#include "TextureListWidget.h"
#include "../FileDialog.h"
#include <filesystem>

TextureListWidget::TextureListWidget()
	: WidgetBase(eTaskPrio_TextureListWidget)
{
}

void TextureListWidget::onRun()
{
	auto& selectTextureNo  = m_pAnimakeData->m_SelectTextureNo;
	auto& texturePathArray = m_pAnimakeData->m_TexturePathArray;
	auto& sampleTextures   = m_pAnimakeData->m_SampleTextures;

	ImGui::Begin("textures");
	{
		if (ImGui::BeginListBox("##textureList"))
		{
			if (ImGui::Selectable("none", selectTextureNo == -1))
			{
				selectTextureNo = -1;
			}
			const auto& texCount = texturePathArray.size();
			for (std::size_t i = 0; i < texCount; i++)
			{
				if (ImGui::Selectable(texturePathArray[i].c_str(), i == selectTextureNo))
				{
					selectTextureNo = i;
					break;
				}
			}
			ImGui::EndListBox();
		}
		if (ImGui::Button("add##texture_add"))
		{
			std::wstring_view filter = L"画像ファイル(*.png)\0*.png\0All(*.*)\0 * .*\0\0";
			std::wstring_view defext = L"png";
			WCHAR path[PATH_MAX];
			bool  isLoadArray = false;
			if (FileDialog::Open(nullptr, FileDialog::Mode::Open, L"画像を開く", filter, defext, path, isLoadArray))
			{
				if (isLoadArray)
				{
					std::wstring currentPath;
					std::vector<std::wstring> filePathArray;
					FileDialog::SeparatePath(path, filePathArray, &currentPath);
					for (const auto& filePath : filePathArray)
					{
						auto fullPath = currentPath + L"\\" + filePath;
						auto tmp = wide_to_sjis(fullPath);
						sampleTextures.push_back(std::make_shared<Sample::Texture>(tmp.c_str()));
						auto relativePath = FileDialog::ChangeRelativePath(tmp, m_pAnimakeData->m_CurrentPath);
						texturePathArray.push_back(relativePath.c_str());
					}
				}
				else
				{
					auto tmp = wide_to_sjis(path);
					sampleTextures.push_back(std::make_shared<Sample::Texture>(tmp.c_str()));
					auto relativePath = FileDialog::ChangeRelativePath(tmp, m_pAnimakeData->m_CurrentPath);
					texturePathArray.push_back(relativePath.c_str());
				}
			}
		} ImGui::SameLine();
		if (ImGui::Button("erase##texture_erase"))
		{
			if (sampleTextures.size() > 0)
			{
				sampleTextures.erase(sampleTextures.begin() + selectTextureNo);
				texturePathArray.erase(texturePathArray.begin() + selectTextureNo);
				if (sampleTextures.size() == 0)
				{
					selectTextureNo = -1;
				}
				else
				{
					selectTextureNo = std::clamp(selectTextureNo, 0, static_cast<std::int32_t>(sampleTextures.size()) - 1);
				}
			}
		}
	}
	ImGui::End();
}
