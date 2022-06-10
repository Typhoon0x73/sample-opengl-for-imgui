#include "FrameBuffer.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
FrameBuffer::FrameBuffer()
: id_(0)
, width_(0)
, height_(0)
, color_() 
, depth_() {
}

/**
 * @brief		デストラクタ
 */
FrameBuffer::~FrameBuffer() {
	Release();
}

/**
 * @brief		生成
 * @param[in]	w		幅
 * @param[in]	h		高さ
 * @return		true	成功
 *				false	失敗
 */
bool FrameBuffer::Create(const int w, const int h) {
	//サイズ保存
	width_ = w;
	height_ = h;
	// フレームバッファオブジェクト、デプスとカラー用のテクスチャを作成
	glGenFramebuffersEXT(1, &id_);
	GL_ERROR_RETURN("フレームバッファの作成に失敗...", false);
	color_ = std::make_shared<Texture>();
	color_->Create(w, h, Texture::FormatType::R8G8B8A8);
	depth_ = std::make_shared<Texture>();
	depth_->Create(w, h, Texture::FormatType::Depth);

	// テクスチャをフレームバッファオブジェクトにバインド
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id_);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_->ID(), 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth_->ID(), 0);
	GL_ERROR_RETURN("フレームバッファのバインドに失敗...", false);

	// デフォルトのターゲットに戻す
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	return true;
}

/**
 * @brief		描画用スプライト生成
 * @return		true	成功
 *				false	失敗
 */
SpritePtr FrameBuffer::CreateSprite(ShaderPtr shader) {
	SpritePtr sprite = std::make_shared<Sprite>();
	sprite->YFlip(true);
	sprite->Create(color_, shader);
	sprite->RefreshMatrix();
	return sprite;
}

/**
 * @brief		バインド
 * @return		true	成功
 *				false	失敗
 */
bool FrameBuffer::Bind() {
	// バッファを変更
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id_);
	GL_ERROR_RETURN("フレームバッファのバインドに失敗...", false);
	glViewport(0, 0, width_, height_);
	return true;
}

/**
 * @brief		解放処理
 */
void FrameBuffer::Release() {
	if (id_ == 0)
	{
		return;
	}
	glDeleteFramebuffersEXT(1, &id_);
	id_ = 0;
	color_->Release();
	depth_->Release();
}