#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class Buffer
	{
	private:
		/** �o�b�t�@ID */
		GLuint			id_;
		/** �o�b�t�@�^�C�v */
		GLenum			type_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Buffer();
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Buffer();

		/**
		 * @brief		�o�b�t�@�̐���
		 * @param[in]	type	�o�b�t�@�̎��
		 * @param[in]	size	�o�b�t�@�T�C�Y
		 * @param[in]	data	�o�b�t�@�Ɋi�[����f�[�^
		 * @param[in]	usage	�o�b�t�@�̎g�p�@
		 * @return		true	��������
		 *				false	�������s
		 */
		bool Create(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage);
		/**
		 * @brief		�o�b�t�@�ւ̃f�[�^��������
		 * @param[in]	offset	�������݃I�t�Z�b�g
		 * @param[in]	size	�������݃T�C�Y
		 * @param[in]	data	�o�b�t�@�Ɋi�[����f�[�^
		 * @return		true	�������ݐ���
		 *				false	�������ݎ��s
		 */
		bool SubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const GLuint ID() const noexcept { return id_; }
	};

}