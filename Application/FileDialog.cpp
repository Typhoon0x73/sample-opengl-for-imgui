#include "FileDialog.h"
#include <filesystem>

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="hWnd">�n���h��</param>
/// <param name="mode">�_�C�A���O�̃��[�h</param>
/// <param name="Title">�_�C�A���O�̃^�C�g��</param>
/// <param name="Filter">�J���t�@�C���̃t�B���^</param>
/// <param name="DefExt">�J���t�@�C���̊g���q</param>
/// <param name="path">�p�X�̏o�͐�</param>
/// <param name="bOutArray">�����t�@�C�����I������Ă��邩�̃t���O�o�͐�</param>
/// <returns></returns>
/// <created>���̂���,2020/11/11</created>
/// <changed>���̂���,2020/11/11</changed>
// ********************************************************************************
bool FileDialog::Open(HWND hWnd, Mode mode, std::wstring_view Title, std::wstring_view Filter, std::wstring_view DefExt, LPWSTR path, bool& bOutArray) {
    //�t�@�C���_�C�A���O�p�\����
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner   = hWnd;
    ofn.lpstrFile   = path;
    ofn.lpstrFilter = Filter.data();
    ofn.lpstrDefExt = DefExt.data();
    ofn.nMaxFile    = MAX_PATH;
    ofn.lpstrTitle  = Title.data();

    memset(path, 0, MAX_PATH);

    if (mode == Mode::Open) {
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
        if (!GetOpenFileName(&ofn)) {
            return false;
        }
        if (ofn.nFileExtension == 0) {
            bOutArray = true;
        }
    }
    else if (mode == Mode::Save) {
        ofn.Flags = OFN_OVERWRITEPROMPT;
        if (!GetSaveFileName(&ofn)) {
            return false;
        }
    }

    return true;
}

#if _MSVC_LANG >= 201703L //! C++17�ȍ~�̋@�\���g�p

// ********************************************************************************
/// <summary>
/// �J�����g�f�B���N�g������̑��΃p�X�֕ϊ�
/// </summary>
/// <param name="path">�ϊ���������΃p�X</param>
/// <param name="base">�w��ʒu�F��������̑��΃p�X�ɂȂ�</param>
/// <returns>�x�[�X����p�X�܂ł̑��΃p�X</returns>
/// <created>���̂���,2020/11/11</created>
/// <changed>���̂���,2020/11/11</changed>
// ********************************************************************************
std::string FileDialog::ChangeRelativePath(std::string_view path, std::string_view base) {
    std::filesystem::path sfp = path;
    std::filesystem::path bfp = base;
    bool path_absolute = sfp.is_absolute();
    bool base_absolute = bfp.is_absolute();
    if (!path_absolute) {
        sfp = ChangeFullPath(sfp.string().data());
    }
    if (!base_absolute) {
        bfp = ChangeFullPath(bfp.string().data());
    }
    return std::filesystem::relative(sfp, bfp).string();
}

// ********************************************************************************
/// <summary>
/// ���΃p�X�����΃p�X�ւ̕ϊ�
/// </summary>
/// <param name="path">�ϊ����������΃p�X</param>
/// <returns>��΃p�X</returns>
/// <created>���̂���,2020/11/11</created>
/// <changed>���̂���,2020/11/11</changed>
// ********************************************************************************
std::string FileDialog::ChangeFullPath(std::string_view path) {
    return std::filesystem::absolute(path).string();
}

#endif

// ********************************************************************************
/// <summary>
/// �ŏ���\0�ȍ~��\0��؂�̕�����z���\0\0�܂ŕ�������B
/// </summary>
/// <param name="pPath">������z��</param>
/// <param name="outArray">������̕�������i�[����z��</param>
/// <param name="outCurrentDirPath">�ŏ���\0�܂ł̕�����̊i�[�ꏊ</param>
/// <created>���̂���,2020/11/11</created>
/// <changed>���̂���,2020/11/11</changed>
// ********************************************************************************
void FileDialog::SeparatePath(WCHAR* pPath, std::vector<std::wstring>& outArray, std::wstring* outCurrentDirPath) {
    // �����̒�����ۑ�����p�̔z��
    std::vector<int> lengthArray;
    int pathLength = wcslen(pPath);

    // �J�����g�f�B���N�g���̏o�͐悪����ꍇ�A�o�͂���B
    if (outCurrentDirPath) {
        (*outCurrentDirPath) = pPath;
    }

    int old = 0;
    while (true) {
        lengthArray.push_back(pathLength);
        old = pathLength;

        std::wstring tmp(&pPath[pathLength + 1]);
        pathLength += strlen(wide_to_sjis(tmp).c_str());

        // \0\0�������烋�[�v���ʂ���B
        if ((pathLength - old) == 0) {
            // �Ō�̕�����f�[�^(\0\0)�̒����͕K�v�Ȃ��̂ŏ����Ă����B
            lengthArray.pop_back();
            break;
        }
        pathLength++;
    }

    // ������𕪉����ĕۑ����Ă����B
    for (const auto& it : lengthArray) {
        outArray.push_back(&pPath[it + 1]);
    }
}
