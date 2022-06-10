#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"
#include	"Camera.h"

namespace Sample {

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

		GraphicsController()
		: window_(nullptr)
		, currentCamera_()
		, width_(0)
		, height_(0) {
		}
		virtual ~GraphicsController() = default;
	public:
		/**
		 * @brief		初期化
		 */
		void Initialize(GLFWwindow* w) {
			window_ = w;
			glfwGetWindowSize(w, &width_, &height_);
		}

		/**
		 * @brief		ターゲットのリセット
		 */
		void ResetTarget() {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			glViewport(0, 0, width_, height_);
		}

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