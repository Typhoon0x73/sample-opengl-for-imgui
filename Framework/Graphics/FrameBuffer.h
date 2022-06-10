#pragma once

#include	"Sprite.h"

namespace Sample {

	class FrameBuffer
	{
	private:
		/** �o�b�t�@ID */
		GLuint			id_;
		/** �� */
		GLint			width_;
		/** ���� */
		GLint			height_;

		/** �F��� */
		TexturePtr		color_;
		/** �[�x��� */
		TexturePtr		depth_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FrameBuffer();

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~FrameBuffer();

		/**
		 * @brief		����
		 * @param[in]	w		��
		 * @param[in]	h		����
		 * @return		true	����
		 *				false	���s
		 */
		bool Create(const int w, const int h);

		/**
		 * @brief		�`��p�X�v���C�g����
		 * @return		true	����
		 *				false	���s
		 */
		SpritePtr CreateSprite(ShaderPtr shader);

		/**
		 * @brief		�o�C���h
		 * @return		true	����
		 *				false	���s
		 */
		bool Bind();

		/**
		 * @brief		�������
		 */
		void Release();

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const GLuint ID() const noexcept { return id_; }
		const GLint Width() const noexcept { return width_; }
		const GLint Height() const noexcept { return height_; }
		const TexturePtr Color() const { return color_; }
		const TexturePtr Depth() const { return depth_; }
	};
	using FrameBufferPtr = std::shared_ptr< FrameBuffer >;

}