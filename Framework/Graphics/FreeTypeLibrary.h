#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"

namespace Sample {

	/**
	 * @brief		�`��Ǘ�
	 */
	class FreeTypeLibrary : public Singleton<FreeTypeLibrary>
	{
		friend class Singleton<FreeTypeLibrary>;
	private:
		/** FreeType�p���C�u���� */
		FT_Library			library_;

		/** FreeType�p�t�H���g���X�g */
		struct Face {
			/** �t�H���g�� */
			std::string		name;
			/** �t�H���g�T�C�Y */
			FT_UInt			size;
			/** FreeType�t�H���g */
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
		 * @brief		������
		 */
		void Initialize() {
			assert(library_ == nullptr);
			FT_Init_FreeType(&library_);
		}

		/**
		 * @brief		������
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
		 * @brief		�t�H���g����
		 * @param[in]	name		�t�H���g��
		 * @param[in]	size		�t�H���g�T�C�Y
		 */
		bool CreteFace(const char* name, uint32_t size)
		{
			//���C�u����������
			if (library_ == nullptr)
			{
				Initialize();
			}
			//���łɂ���ꍇ�G���[
			auto result = std::find_if(faceList_.begin(), faceList_.end(),
				[&](const Face& d)
				{
					return d.name == name && d.size == size;
				}
			);
			assert(result == faceList_.end());
			//Face�쐬
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
		 * @brief		�t�H���g����
		 * @param[in]	name		�t�H���g��
		 * @param[in]	size		�t�H���g�T�C�Y
		 * @param[in]	text		����
		 */
		FT_GlyphSlot CreateChar(const char* name, unsigned int size, FT_ULong text)
		{
			//�����֐�
			auto findFunc = [&](const Face& d)
			{
				return d.name == name && d.size == size;
			};

			//���݂��Ȃ��ꍇ����
			auto face = std::find_if(faceList_.begin(), faceList_.end(), findFunc);
			//���݂��Ȃ��̂Ő���
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
			//��������
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