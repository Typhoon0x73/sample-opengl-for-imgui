#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"
#include	"Camera.h"

namespace Sample {

    // FWD
    class FrameBuffer;
    class Sprite;
    class Shader;
    using FrameBufferPtr = std::shared_ptr<FrameBuffer>;
    using SpritePtr      = std::shared_ptr<Sprite>;
    using ShaderPtr      = std::shared_ptr<Shader>;

	/**
	 * @brief		描画管理
	 */
	class GraphicsController : public Singleton<GraphicsController>
	{
		friend class Singleton<GraphicsController>;
	private:
		/** ウインドウ */
		GLFWwindow*									window_;
		/** メインカメラ */
		CameraPtr									currentCamera_;
		/**	画面幅 */
		int											width_;
		/**	画面高さ */
		int											height_;
        /** 描画用バッファ */
        FrameBufferPtr                              frameBuffer_;
        /** 描画用スプライト */
        SpritePtr                                   frameSprite_;
        /** シェーダー */
		ShaderPtr                                   shader_;

		GraphicsController()
		: window_(nullptr)
		, currentCamera_(nullptr)
		, width_(0)
		, height_(0)
		, frameBuffer_(nullptr)
		, frameSprite_(nullptr)
        , shader_(nullptr) {
		}
		virtual ~GraphicsController() = default;
	public:
		/**
		 * @brief		初期化
		 */
        void Initialize(GLFWwindow* w);

        /**
         * @brief		描画用バッファの生成
         */
        void CreateBuffer();

		/**
		 * @brief		ターゲットのリセット
		 */
		void ResetTarget() {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			glViewport(0, 0, width_, height_);
		}

        /**
         * @brief		描画開始
         */
        void RenderBegin();

        /**
         * @brief		描画
         */
        void RenderEnd();

		/**
		 * @brief		利用中のカメラの設定
		 * @param[in]	cam		利用中のカメラ
		 */
		void Camera(CameraPtr& cam) {
			currentCamera_ = cam;
		}

		/**
		 * @brief		利用中のカメラの取得
		 * @return		利用中のカメラ
		 */
		const CameraPtr& Camera() const {
			return currentCamera_;
		}

		/**
		 * @brief		利用中のシェーダーの取得
		 * @return		利用中のシェーダー
		 */
		const ShaderPtr& Shader() const {
			return shader_;
		}

		/**
		 * @brief		初期のフレームバッファの取得
		 * @return		初期のフレームバッファ
		 */
		const FrameBufferPtr& FrameBuffer() const {
			return frameBuffer_;
		}

		/**
		 * @brief		初期のスプライトの取得
		 * @return		初期のスプライト
		 */
		const SpritePtr& Sprite() const {
			return frameSprite_;
		}

		/**
		 * @brief		画面
		 */
		GLFWwindow* Window() const noexcept { return window_; }
		/**
		 * @brief		画面幅の取得
		 */
		const GLint ScreenWidth() const noexcept { return width_; }
		/**
		 * @brief		画面高さの取得
		 */
		const GLint ScreenHeight() const noexcept { return height_; }
	};

}