#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"

namespace Sample {

	/**
	 * @brief		描画管理
	 */
	class FreeTypeLibrary : public Singleton<FreeTypeLibrary>
	{
		friend class Singleton<FreeTypeLibrary>;
	private:
		/** FreeType用ライブラリ */
		FT_Library			library_;

		/** FreeType用フォントリスト */
		struct Face {
			/** フォント名 */
			std::string		name;
			/** フォントサイズ */
			FT_UInt			size;
			/** FreeTypeフォント */
			FT_Face			face;
			/** FreeType */
			FT_GlyphSlot	slot;
		};
		std::vector< Face >	faceList_;

		FreeTypeLibrary()
			: library_()
			, faceList_() {
		}
		virtual ~FreeTypeLibrary() {
			Release();
		}
	public:
		/**
		 * @brief		初期化
		 */
		void Initialize() {
			assert(library_ == nullptr);
			FT_Init_FreeType(&library_);
		}

		/**
		 * @brief		初期化
		 */
		void Release() {
			assert(library_ == nullptr);
			for (auto& face : faceList_)
			{
				FT_Done_Face(face.face);
			}
			faceList_.clear();
			FT_Done_FreeType(library_);
			library_ = nullptr;
		}

		/**
		 * @brief		フォント生成
		 * @param[in]	name		フォント名
		 * @param[in]	size		フォントサイズ
		 */
		bool CreteFace(const char* name, uint32_t size)
		{
			//ライブラリ初期化
			if (library_ == nullptr)
			{
				Initialize();
			}
			//すでにある場合エラー
			auto result = std::find_if(faceList_.begin(), faceList_.end(),
				[&](const Face& d)
				{
					return d.name == name && d.size == size;
				}
			);
			assert(result == faceList_.end());
			//Face作成
			FT_Face face;
			FT_Error err = FT_New_Face(library_, name, 0, &face);
			if (err == FT_Err_Unknown_File_Format)
			{
				ERROR_LOG("UnSupport Fonts Format");
				return false;
			}
			else if (err)
			{
				ERROR_LOG("Fonts File not found");
				return false;
			}
			FT_Set_Pixel_Sizes(face, size, 0);
			faceList_.push_back({ name, size, face, face->glyph });
			return true;
		}

		/**
		 * @brief		フォント生成
		 * @param[in]	name		フォント名
		 * @param[in]	size		フォントサイズ
		 * @param[in]	text		文字
		 */
		FT_GlyphSlot CreateChar(const char* name, unsigned int size, FT_ULong text)
		{
			//検索関数
			auto findFunc = [&](const Face& d)
			{
				return d.name == name && d.size == size;
			};

			//存在しない場合生成
			auto face = std::find_if(faceList_.begin(), faceList_.end(), findFunc);
			//存在しないので生成
			if (face == faceList_.end())
			{
				if (CreteFace(name, size))
				{
					face = std::find_if(faceList_.begin(), faceList_.end(), findFunc);
				}
				if (face == faceList_.end())
				{
					return nullptr;
				}
			}
			//文字生成
			FT_Error err = FT_Load_Char(face->face, text, FT_LOAD_RENDER);
			if (err)
			{
				ERROR_LOG("FreeType LoadChar Error!!");
				return nullptr;
			}
			return face->slot;
		}
	};

}