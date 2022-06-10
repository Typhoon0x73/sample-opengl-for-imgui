#pragma once

#include	"ShaderParameterBind.h"

namespace Sample {

	/**
	 * @brief		シェーダーに値を設定づけるためのクラス
	 */
	class ShaderParameterBind1F : public ShaderParameterBind
	{
	protected:
		/** 対応する値 */
		GLfloat value_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		ShaderParameterBind1F(ShaderPtr shader, const char* name)
			: ShaderParameterBind(shader, name)
			, value_(0)
		{
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~ShaderParameterBind1F() {
		}

		/**
		 * @brief		値のバインド
		 */
		virtual void Bind() {
			assert(shader_ != nullptr);
			glUniform1f(location_, value_);
		}

		/**
		 * @brief		値の設定
		 */
		void Value(GLfloat v) {
			value_ = v;
		}
	};
	using ShaderParameterBind1FPtr = std::shared_ptr< ShaderParameterBind1F >;

}