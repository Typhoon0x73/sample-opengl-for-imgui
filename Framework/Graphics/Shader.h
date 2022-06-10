#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		�V�F�[�_�[���������߂̃N���X
	 */
	class Shader : public ResourceBase
	{
	private:
		/** �V�F�[�_�[ID */
		GLuint		id_;

		/** �r���[�v���W�F�N�V�����s�� */
		GLint		matVP_;

		/** ���f���s�� */
		GLint		matModel_;

		/**
		 * @brief		�V�F�[�_�[�̃R���p�C������
		 */
		GLuint Compile(GLenum type, const char* fname);
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Shader();
		/**
		 * @brief		�R���X�g���N�^
		 * @param[in]	name	�V�F�[�_�[(���_�V�F�[�_�[/�t���O�����g�V�F�[�_�[�Ŗ��O�w��)
		 */
		Shader(const char* name);
		/**
		 * @brief		�R���X�g���N�^
		 * @param[in]	vname	���_�V�F�[�_�[
		 * @param[in]	fname	�t���O�����g�V�F�[�_�[
		 */
		Shader(const char* vname, const char* fname);
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Shader();

		/**
		 * @brief		�V�F�[�_�[�̐���
		 * @param[in]	vname	���_�V�F�[�_�[
		 * @param[in]	fname	�t���O�����g�V�F�[�_�[
		 * @return		true	��������
		 *				false	�������s
		 */
		bool Load(const char* vname, const char* fname);
		/**
		 * @brief		�V�F�[�_�[�̗L����
		 * @return		true	����
		 *				false	���s
		 */
		bool Enable();

		/**
		 * @brief		�������
		 */
		void Release();

		/**
		 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
		 */
		bool BindTexture(GLuint no, GLuint id);
		/**
		 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
		 */
		bool BindSampler(GLuint no, GLuint id);
		/**
		 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
		 */
		bool SetViewProjectionMatrix(const float* fv);
		/**
		 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
		 */
		bool SetModelMatrix(const float* fv);

		/**
		 * @brief		�V�F�[�_�[�p�����[�^�[�̃��P�[�V�����擾
		 */
		GLint GetUniformLocation(const char* name);

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const GLuint ID() const noexcept { return id_; }
	};
	using ShaderPtr = std::shared_ptr< Shader >;

}