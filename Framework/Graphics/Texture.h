#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		画像を扱うためのクラス
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
		/** テクスチャID */
		GLuint			id_;
		/** 幅 */
		GLint			width_;
		/** 高さ */
		GLint			height_;
		/** 利用フォーマット */
		FormatType		format_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Texture();

		/**
		 * @brief		コンストラクタ
		 *				生成と同時に読み込みをおこなう
		 * @param[in]	name	読み込むテクスチャ名
		 */
		Texture(const char* name);

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Texture();

		/**
		 * @brief		読み込み
		 * @param[in]	name	読み込むテクスチャ名
		 * @return		true	読み込み成功
		 *				false	読み込み失敗
		 */
		bool Load(const char* name);

		/**
		 * @brief		生成
		 * @param[in]	w		幅
		 * @param[in]	h		高さ
		 * @param[in]	format	フォーマット
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Create(const int w, const int h, const FormatType format);

		/**
		 * @brief		テクスチャへのデータ書き込み
		 * @param[in]	offX	書き込みオフセット
		 * @param[in]	offY	書き込みオフセット
		 * @param[in]	w		書き込みサイズ
		 * @param[in]	h		書き込みサイズ
		 * @param[in]	pixels	テクスチャに格納するデータ
		 * @return		true	書き込み成功
		 *				false	書き込み失敗
		 */
		bool SubData(GLint offX, GLint offY, GLint w, GLint h, const GLvoid* pixels);

		/**
		 * @brief		解放処理
		 */
		void Release();

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const GLuint ID() const noexcept { return id_; }
		const GLint Width() const noexcept { return width_; }
		const GLint Height() const noexcept { return height_; }

	};
	using TexturePtr = std::shared_ptr< Texture >;

}