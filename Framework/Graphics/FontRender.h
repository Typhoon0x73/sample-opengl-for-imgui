#pragma once

#include	"FontAtlas.h"
#include	"SpriteBatch.h"

namespace Sample {

	/**
	 * @brief		�t�H���g��`�悷�邽�߂̃N���X
	 */
	class FontRender
	{
	protected:
		/** ���p����X�v���C�g */
		SpriteBatchPtr	sprite_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FontRender()
			: sprite_() {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~FontRender() {
		}

		/**
		 * @brief		����
		 * @param[in]	shader		�`��p�V�F�[�_�[
		 * @return		true		��������
		 *				false		�������s
		 */
		bool Create(ShaderPtr shader) {
			//�X�v���C�g����
			sprite_ = std::make_shared<SpriteBatch>();
			sprite_->Create(shader);
			return true;
		}

		/**
		 * @brief		�`��
		 * @param[in]	x			�`��ʒu
		 * @param[in]	y			�`��ʒu
		 * @param[in]	str			�`�敶����
		 * @param[in]	font		�`��p�t�H���g
		 */
		bool Render(float x, float y, const Vector4F& color, const std::string& str, FontAtlasPtr& font) {
			//�X���C�X�}�b�v
			const auto& map = font->Slices();
			//�e�N�X�`��
			auto tex = font->Texture();
			//�`����W
			float dx = x;
			float dy = y;

			//�����𕪊����ĕ`��o�^
			sprite_->Reset();
			for (size_t i = 0; i < str.size(); i++)
			{
				//�`�敶��
				char text[3] = { 0 };
				if (IsDBCSLeadByte(str[i]))
				{
					text[0] = str[i]; text[1] = str[i + 1];
					i++;
				}
				else
				{
					//���s�����͎��̍s�֎�����
					if (str[i] == '\n')
					{
						dx = x;
						dy += font->Font()->Size();
						continue;
					}
					text[0] = str[i];
				}
				//�}�b�v���猟��
				auto slice = map.find(text);
				if (slice == map.end())
				{
					if (!font->Add(text))
					{
						return false;
					}
					slice = map.find(text);
					if (slice == map.end())
					{
						return false;
					}
				}
				sprite_->RenderRegister(tex, Vector3F(dx, dy, 0), color, slice->second);
				dx += slice->second.Width();
			}
			sprite_->RefreshVertex();
			sprite_->Render();
			return true;
		}

	};
	using FontRenderPtr = std::shared_ptr< FontRender >;

}