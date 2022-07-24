#include "FileDialog.h"
#include <filesystem>

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="hWnd">ハンドル</param>
/// <param name="mode">ダイアログのモード</param>
/// <param name="Title">ダイアログのタイトル</param>
/// <param name="Filter">開くファイルのフィルタ</param>
/// <param name="DefExt">開くファイルの拡張子</param>
/// <param name="path">パスの出力先</param>
/// <param name="bOutArray">複数ファイルが選択されているかのフラグ出力先</param>
/// <returns></returns>
/// <created>いのうえ,2020/11/11</created>
/// <changed>いのうえ,2020/11/11</changed>
// ********************************************************************************
bool FileDialog::Open(HWND hWnd, Mode mode, std::wstring_view Title, std::wstring_view Filter, std::wstring_view DefExt, LPWSTR path, bool& bOutArray) {
    //ファイルダイアログ用構造体
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

#if _MSVC_LANG >= 201703L //! C++17以降の機能を使用

// ********************************************************************************
/// <summary>
/// カレントディレクトリからの相対パスへ変換
/// </summary>
/// <param name="path">変換したい絶対パス</param>
/// <param name="base">指定位置：ここからの相対パスになる</param>
/// <returns>ベースからパスまでの相対パス</returns>
/// <created>いのうえ,2020/11/11</created>
/// <changed>いのうえ,2020/11/11</changed>
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
/// 相対パスから絶対パスへの変換
/// </summary>
/// <param name="path">変換したい相対パス</param>
/// <returns>絶対パス</returns>
/// <created>いのうえ,2020/11/11</created>
/// <changed>いのうえ,2020/11/11</changed>
// ********************************************************************************
std::string FileDialog::ChangeFullPath(std::string_view path) {
    return std::filesystem::absolute(path).string();
}

#endif

// ********************************************************************************
/// <summary>
/// 最初の\0以降の\0区切りの文字列配列を\0\0まで分解する。
/// </summary>
/// <param name="pPath">文字列配列</param>
/// <param name="outArray">分解後の文字列を格納する配列</param>
/// <param name="outCurrentDirPath">最初の\0までの文字列の格納場所</param>
/// <created>いのうえ,2020/11/11</created>
/// <changed>いのうえ,2020/11/11</changed>
// ********************************************************************************
void FileDialog::SeparatePath(WCHAR* pPath, std::vector<std::wstring>& outArray, std::wstring* outCurrentDirPath) {
    // 文字の長さを保存する用の配列
    std::vector<int> lengthArray;
    int pathLength = wcslen(pPath);

    // カレントディレクトリの出力先がある場合、出力する。
    if (outCurrentDirPath) {
        (*outCurrentDirPath) = pPath;
    }

    int old = 0;
    while (true) {
        lengthArray.push_back(pathLength);
        old = pathLength;

        std::wstring tmp(&pPath[pathLength + 1]);
        pathLength += strlen(wide_to_sjis(tmp).c_str());

        // \0\0が来たらループをぬける。
        if ((pathLength - old) == 0) {
            // 最後の文字列データ(\0\0)の長さは必要ないので消しておく。
            lengthArray.pop_back();
            break;
        }
        pathLength++;
    }

    // 文字列を分解して保存していく。
    for (const auto& it : lengthArray) {
        outArray.push_back(&pPath[it + 1]);
    }
}
