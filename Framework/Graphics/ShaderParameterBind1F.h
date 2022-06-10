#pragma once

#include	"ShaderParameterBind.h"

namespace Sample {

	/**
	 * @brief		�V�F�[�_�[�ɒl��ݒ�Â��邽�߂̃N���X
	 */
	class ShaderParameterBind1F : public ShaderParameterBind
	{
	protected:
		/** �Ή�����l */
		GLfloat value_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ShaderParameterBind1F(ShaderPtr shader, const char* name)
			: ShaderParameterBind(shader, name)
			, value_(0)
		{
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ShaderParameterBind1F() {
		}

		/**
		 * @brief		�l�̃o�C���h
		 */
		virtual void Bind() {
			assert(shader_ != nullptr);
			glUniform1f(location_, value_);
		}

		/**
		 * @brief		�l�̐ݒ�
		 */
		void Value(GLfloat v) {
			value_ = v;
		}
	};
	using ShaderParameterBind1FPtr = std::shared_ptr< ShaderParameterBind1F >;

}