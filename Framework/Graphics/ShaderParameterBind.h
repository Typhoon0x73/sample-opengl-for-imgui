#pragma once

#include	"Shader.h"

namespace Sample {

	/**
	 * @brief		�V�F�[�_�[�ɒl��ݒ�Â��邽�߂̃N���X
	 */
	class ShaderParameterBind
	{
	protected:
		/** �Ή�����V�F�[�_�[ */
		ShaderPtr shader_;

		/** �p�����[�^�[���P�[�V���� */
		GLint location_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ShaderParameterBind(ShaderPtr shader, const char* name)
			: location_(shader->GetUniformLocation(name))
			, shader_(shader)
		{
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ShaderParameterBind() {
			shader_.reset();
			location_ = 0;
		}

		/**
		 * @brief		�l�̃o�C���h
		 */
		virtual void Bind() = 0;

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const GLint ID() const noexcept { return location_; }
	};
	using ShaderParameterBindPtr = std::shared_ptr< ShaderParameterBind >;
	using ShaderParameterBindList = std::vector< ShaderParameterBindPtr >;

}