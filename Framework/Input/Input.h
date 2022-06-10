#pragma once

#include	"IInput.h"

namespace Sample {

	class Input : public IInput
	{
	private:
		/** ウインドウ */
		GLFWwindow*									window_;

		/** マウス座標 */
		double										mouseX_;

		/** マウス座標 */
		double										mouseY_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Input(GLFWwindow* w)
			: window_(w)
			, mouseX_(0)
			, mouseY_(0) {
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Input() {
		}

		/**
		 * @brief		入力の更新
		 *				Framework::Runにて呼び出し
		 */
		void Refresh() override {
			//マウス位置の取得
			glfwGetCursorPos(window_, &mouseX_, &mouseY_);
		}

		/**
		 * @brief		キー状態の取得
		 * @param[in]	keycode	キーコード
		 */
		int GetKeyState(const int keycode) noexcept override {
			return glfwGetKey(window_, keycode);
		}

		/**
		 * @brief		マウス横位置
		 * @return		マウス横位置
		 */
		const double GetMouseX() const noexcept override {
			return mouseX_;
		}

		/**
		 * @brief		マウス縦位置
		 * @return		マウス縦位置
		 */
		const double GetMouseY() const noexcept override {
			return mouseY_;
		}
	};

}