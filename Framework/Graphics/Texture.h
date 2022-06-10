#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		�摜���������߂̃N���X
	 */
	class Texture : public ResourceBase
	{
	public:
		enum class FormatType {
			R8G8B8,
			R8G8B8A8,
			Depth,
			Unknown,
		};
	protected:
		/** �e�N�X�`��ID */
		GLuint			id_;
		/** �� */
		GLint			width_;
		/** ���� */
		GLint			height_;
		/** ���p�t�H�[�}�b�g */
		FormatType		format_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Texture();

		/**
		 * @brief		�R���X�g���N�^
		 *				�����Ɠ����ɓǂݍ��݂������Ȃ�
		 * @param[in]	name	�ǂݍ��ރe�N�X�`����
		 */
		Texture(const char* name);

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Texture();

		/**
		 * @brief		�ǂݍ���
		 * @param[in]	name	�ǂݍ��ރe�N�X�`����
		 * @return		true	�ǂݍ��ݐ���
		 *				false	�ǂݍ��ݎ��s
		 */
		bool Load(const char* name);

		/**
		 * @brief		����
		 * @param[in]	w		��
		 * @param[in]	h		����
		 * @param[in]	format	�t�H�[�}�b�g
		 * @return		true	����
		 *				false	���s
		 */
		bool Create(const int w, const int h, const FormatType format);

		/**
		 * @brief		�e�N�X�`���ւ̃f�[�^��������
		 * @param[in]	offX	�������݃I�t�Z�b�g
		 * @param[in]	offY	�������݃I�t�Z�b�g
		 * @param[in]	w		�������݃T�C�Y
		 * @param[in]	h		�������݃T�C�Y
		 * @param[in]	pixels	�e�N�X�`���Ɋi�[����f�[�^
		 * @return		true	�������ݐ���
		 *				false	�������ݎ��s
		 */
		bool SubData(GLint offX, GLint offY, GLint w, GLint h, const GLvoid* pixels);

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

	};
	using TexturePtr = std::shared_ptr< Texture >;

}