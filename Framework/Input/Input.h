#pragma once

#include	"IInput.h"

namespace Sample {

	class Input : public IInput
	{
	private:
		/** �E�C���h�E */
		GLFWwindow*									window_;

		/** �}�E�X���W */
		double										mouseX_;

		/** �}�E�X���W */
		double										mouseY_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Input(GLFWwindow* w)
			: window_(w)
			, mouseX_(0)
			, mouseY_(0) {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Input() {
		}

		/**
		 * @brief		���͂̍X�V
		 *				Framework::Run�ɂČĂяo��
		 */
		void Refresh() override {
			//�}�E�X�ʒu�̎擾
			glfwGetCursorPos(window_, &mouseX_, &mouseY_);
		}

		/**
		 * @brief		�L�[��Ԃ̎擾
		 * @param[in]	keycode	�L�[�R�[�h
		 */
		int GetKeyState(const int keycode) noexcept override {
			return glfwGetKey(window_, keycode);
		}

		/**
		 * @brief		�}�E�X���ʒu
		 * @return		�}�E�X���ʒu
		 */
		const double GetMouseX() const noexcept override {
			return mouseX_;
		}

		/**
		 * @brief		�}�E�X�c�ʒu
		 * @return		�}�E�X�c�ʒu
		 */
		const double GetMouseY() const noexcept override {
			return mouseY_;
		}
	};

}