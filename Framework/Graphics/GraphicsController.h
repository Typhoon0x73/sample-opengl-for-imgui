#pragma once

#include	"../Common/Common.h"
#include	"../Common/Singleton.h"
#include	"Camera.h"

namespace Sample {

	/**
	 * @brief		�`��Ǘ�
	 */
	class GraphicsController : public Singleton<GraphicsController>
	{
		friend class Singleton<GraphicsController>;
	private:
		/** �E�C���h�E */
		GLFWwindow*									window_;
		/** ���C���J���� */
		CameraPtr									currentCamera_;
		/**	��ʕ� */
		int											width_;
		/**	��ʍ��� */
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
		 * @brief		������
		 */
		void Initialize(GLFWwindow* w) {
			window_ = w;
			glfwGetWindowSize(w, &width_, &height_);
		}

		/**
		 * @brief		�^�[�Q�b�g�̃��Z�b�g
		 */
		void ResetTarget() {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			glViewport(0, 0, width_, height_);
		}

		/**
		 * @brief		���p���̃J�����̐ݒ�
		 * @param[in]	cam		���p���̃J����
		 */
		void Camera(CameraPtr& cam) {
			currentCamera_ = cam;
		}

		/**
		 * @brief		���p���̃J�����̎擾
		 * @return		���p���̃J����
		 */
		const CameraPtr& Camera() const {
			return currentCamera_;
		}

		/**
		 * @brief		���
		 */
		GLFWwindow* Window() const noexcept { return window_; }
		/**
		 * @brief		��ʕ��̎擾
		 */
		const GLint ScreenWidth() const noexcept { return width_; }
		/**
		 * @brief		��ʍ����̎擾
		 */
		const GLint ScreenHeight() const noexcept { return height_; }
	};

}