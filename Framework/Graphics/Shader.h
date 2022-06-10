#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		シェーダーを扱うためのクラス
	 */
	class Shader : public ResourceBase
	{
	private:
		/** シェーダーID */
		GLuint		id_;

		/** ビュープロジェクション行列 */
		GLint		matVP_;

		/** モデル行列 */
		GLint		matModel_;

		/**
		 * @brief		シェーダーのコンパイル命令
		 */
		GLuint Compile(GLenum type, const char* fname);
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Shader();
		/**
		 * @brief		コンストラクタ
		 * @param[in]	name	シェーダー(頂点シェーダー/フラグメントシェーダーで名前指定)
		 */
		Shader(const char* name);
		/**
		 * @brief		コンストラクタ
		 * @param[in]	vname	頂点シェーダー
		 * @param[in]	fname	フラグメントシェーダー
		 */
		Shader(const char* vname, const char* fname);
		/**
		 * @brief		デストラクタ
		 */
		virtual ~Shader();

		/**
		 * @brief		シェーダーの生成
		 * @param[in]	vname	頂点シェーダー
		 * @param[in]	fname	フラグメントシェーダー
		 * @return		true	生成成功
		 *				false	生成失敗
		 */
		bool Load(const char* vname, const char* fname);
		/**
		 * @brief		シェーダーの有効化
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Enable();

		/**
		 * @brief		解放処理
		 */
		void Release();

		/**
		 * @brief		シェーダーへのパラメーター設定
		 */
		bool BindTexture(GLuint no, GLuint id);
		/**
		 * @brief		シェーダーへのパラメーター設定
		 */
		bool BindSampler(GLuint no, GLuint id);
		/**
		 * @brief		シェーダーへのパラメーター設定
		 */
		bool SetViewProjectionMatrix(const float* fv);
		/**
		 * @brief		シェーダーへのパラメーター設定
		 */
		bool SetModelMatrix(const float* fv);

		/**
		 * @brief		シェーダーパラメーターのロケーション取得
		 */
		GLint GetUniformLocation(const char* name);

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const GLuint ID() const noexcept { return id_; }
	};
	using ShaderPtr = std::shared_ptr< Shader >;

}