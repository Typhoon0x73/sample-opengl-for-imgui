#pragma once

#include	"Font.h"
#include	"Texture.h"

namespace Sample {

	/**
	 * @brief		�t�H���g���������߂̃N���X
	 */
	class FontAtlas : public ResourceBase
	{
	protected:
		/** ���p����t�H���g */
		FontPtr			font_;

		/** ���p����e�N�X�`�� */
		TexturePtr		texture_;

		/** �������݃I�t�Z�b�g�ʒu */
		int				destOffsetX;
		/** �������݃I�t�Z�b�g�ʒu */
		int				destOffsetY;

		/** �؂蔲���}�b�v */
		using SliceMap = std::map<std::string, RectangleF>;
		SliceMap		slices_;

		/**
		 * @brief		�R�[�h�̕������۔��f
		 * @return		true		OK
		 *				false		NO
		 */
		bool IsCodeValid(const char s) {
			return !(s == ' ' || s == '\t' || s == '\n' || s == '\r' || s == '\0');
		}
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FontAtlas()
			: ResourceBase()
			, font_()
			, texture_()
			, destOffsetX(0)
			, destOffsetY(0) {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~FontAtlas() {
		}

		/**
		 * @brief		����
		 * @param[in]	fontface	�ǂݍ��ރt�H���g�t�@�C����
		 * @param[in]	fontsize	�t�H���g�T�C�Y
		 * @param[in]	texsize		�e�N�X�`���T�C�Y
		 * @return		true		��������
		 *				false		�������s
		 */
		bool Create(const char* fontface, const uint32_t fontsize, const int texsize) {
			//�t�H���g����
			font_ = std::make_shared<Sample::Font>();
			if (!font_->Create(fontface, fontsize))
			{
				return false;
			}
			//�e�N�X�`������
			texture_ = std::make_shared<Sample::Texture>();
			if (!texture_->Create(texsize, texsize, Texture::FormatType::R8G8B8A8))
			{
				return false;
			}
			return true;
		}

		/**
		 * @brief		�A�g���X�̒ǉ�
		 * @param[in]	str			�ǉ����镶����
		 * @return		true		��������
		 *				false		�������s
		 */
		bool Add(const char* str)
		{
			size_t len = strlen(str);
			for (size_t i = 0; i < len; i++)
			{
				char text[3] = { 0 };
				uint32_t t = 0;
				if (IsDBCSLeadByte(str[i]))
				{
					wchar_t wstr[2];
					MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &str[i], 2, wstr, 2);
					t = wstr[0];
					text[0] = str[i]; text[1] = str[i + 1];
					i++;
				}
				else
				{
					//���p�X�y�[�X�A�^�u�A���s�Ȃǂ̕����̓A�g���X�ɂ͖���
					if (!IsCodeValid(str[i]))
					{
						continue;
					}
					t = str[i];
					text[0] = str[i];
				}
				if (destOffsetX + font_->Size() >= texture_->Width())
				{
					destOffsetX = 0;
					destOffsetY += font_->Size();
					if (destOffsetY + font_->Size() >= texture_->Height())
					{
						ERROR_LOG("Atlas Size Over!!");
						return false;
					}
				}
				//Font����擾
				auto img = font_->CreateCodeBitmap(t);
				if (img == nullptr)
				{
					continue;
				}
				//�f�[�^��RGPA�̌`���ɕύX
				uint8_t* b4Pixels = new uint8_t[img->width * img->height * 4];
				for (int y = 0; y < img->height; y++)
				{
					for (int x = 0; x < img->width; x++)
					{
						b4Pixels[(y * img->width + x) * 4 + 0] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 1] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 2] = img->pixels[y * img->width + x];
						b4Pixels[(y * img->width + x) * 4 + 3] = img->pixels[y * img->width + x];
					}
				}
				//�e�N�X�`���ɓ]��
				texture_->SubData(destOffsetX + img->offsetX, destOffsetY + img->offsetY, img->width, img->height, b4Pixels);
				//�}�b�v�ɓo�^
				slices_[text] = RectangleF((float)destOffsetX, (float)destOffsetY, (float)destOffsetX + img->offsetX + img->width, (float)destOffsetY + img->offsetY + img->height);
				delete[] b4Pixels;
				//���̏������ݏꏊ��
				destOffsetX += font_->Size();
			}
			return true;
		}

		/**
		 * @brief		Font_�ւ�Accessor
		 * @return		�t�H���g
		 */
		const FontPtr Font(void) const { return font_; }

		/**
		 * @brief		Texture_�ւ�Accessor
		 * @return		�e�N�X�`��
		 */
		const TexturePtr Texture(void) const { return texture_; }

		/**
		 * @brief		Slices_�ւ�Accessor
		 * @return		�؂蔲���}�b�v
		 */
		const SliceMap& Slices(void) const { return slices_; }
	};
	using FontAtlasPtr = std::shared_ptr< FontAtlas >;

}