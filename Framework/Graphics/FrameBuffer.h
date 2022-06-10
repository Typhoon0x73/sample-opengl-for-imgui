#pragma once

#include	"Sprite.h"

namespace Sample {

	class FrameBuffer
	{
	private:
		/** バッファID */
		GLuint			id_;
		/** 幅 */
		GLint			width_;
		/** 高さ */
		GLint			height_;

		/** 色情報 */
		TexturePtr		color_;
		/** 深度情報 */
		TexturePtr		depth_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		FrameBuffer();

		/**
		 * @brief		デストラクタ
		 */
		virtual ~FrameBuffer();

		/**
		 * @brief		生成
		 * @param[in]	w		幅
		 * @param[in]	h		高さ
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Create(const int w, const int h);

		/**
		 * @brief		描画用スプライト生成
		 * @return		true	成功
		 *				false	失敗
		 */
		SpritePtr CreateSprite(ShaderPtr shader);

		/**
		 * @brief		バインド
		 * @return		true	成功
		 *				false	失敗
		 */
		bool Bind();

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
		const TexturePtr Color() const { return color_; }
		const TexturePtr Depth() const { return depth_; }
	};
	using FrameBufferPtr = std::shared_ptr< FrameBuffer >;

}