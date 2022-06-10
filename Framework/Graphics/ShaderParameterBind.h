#pragma once

#include	"Shader.h"

namespace Sample {

	/**
	 * @brief		シェーダーに値を設定づけるためのクラス
	 */
	class ShaderParameterBind
	{
	protected:
		/** 対応するシェーダー */
		ShaderPtr shader_;

		/** パラメーターロケーション */
		GLint location_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		ShaderParameterBind(ShaderPtr shader, const char* name)
			: location_(shader->GetUniformLocation(name))
			, shader_(shader)
		{
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~ShaderParameterBind() {
			shader_.reset();
			location_ = 0;
		}

		/**
		 * @brief		値のバインド
		 */
		virtual void Bind() = 0;

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const GLint ID() const noexcept { return location_; }
	};
	using ShaderParameterBindPtr = std::shared_ptr< ShaderParameterBind >;
	using ShaderParameterBindList = std::vector< ShaderParameterBindPtr >;

}