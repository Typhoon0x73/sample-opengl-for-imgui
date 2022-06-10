#pragma once

#include	"../Resource/ResourceBase.h"
#include	"FreeTypeLibrary.h"

namespace Sample {

	/**
	 * @brief		�t�H���g���������߂̃N���X
	 */
	class Font : public ResourceBase
	{
	public:
		/** �t�H���g�摜 */
		struct Image {
			int			offsetX;
			int			offsetY;
			int			width;
			int			height;
			uint8_t*	pixels;
		};
		using ImagePtr = std::shared_ptr< Image >;
	protected:
		/** ���p����t�H���g�T�C�Y */
		uint32_t		size_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Font()
			: ResourceBase()
			, size_(0) {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Font() {
		}

		/**
		 * @brief		�ǂݍ���
		 * @param[in]	name	�ǂݍ��ރt�H���g�t�@�C����
		 * @param[in]	size	�t�H���g�T�C�Y
		 * @return		true	�ǂݍ��ݐ���
		 *				false	�ǂݍ��ݎ��s
		 */
		bool Create(const char* name, const uint32_t size) {
			if (!FreeTypeLibrary::GetInstance().CreteFace(name, size))
			{
				return false;
			}
			name_ = name;
			size_ = size;
			INFO_LOG("�t�H���g" << name << "��ǂݍ���...");
			return true;
		}

		/**
		 * @brief		�w�肳�ꂽ�R�[�h��BMP����
		 * @param[in]	code	�����R�[�h
		 * @return		���������C���[�W
		 */
		ImagePtr CreateCodeBitmap(uint32_t code) {
			FT_GlyphSlot slot = FreeTypeLibrary::GetInstance().CreateChar(name_.c_str(), size_, code);
			if (slot == nullptr)
			{
				return ImagePtr();
			}
			ImagePtr re = std::make_shared<Image>();
			re->offsetX = slot->bitmap_left;
			re->offsetY = size_ - slot->bitmap_top;
			re->width = slot->bitmap.width;
			re->height = slot->bitmap.rows;
			re->pixels = slot->bitmap.buffer;
			return re;
		}

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const uint32_t Size() const noexcept { return size_; }
	};
	using FontPtr = std::shared_ptr< Font >;

}