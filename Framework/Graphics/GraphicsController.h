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
        /** �`��p�o�b�t�@ */
        FrameBufferPtr                              frameBuffer_;
        /** �`��p�X�v���C�g */
        SpritePtr                                   frameSprite_;
        /** �V�F�[�_�[ */
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
		 * @brief		������
		 */
        void Initialize(GLFWwindow* w);

        /**
         * @brief		�`��p�o�b�t�@�̐���
         */
        void CreateBuffer();

		/**
		 * @brief		�^�[�Q�b�g�̃��Z�b�g
		 */
		void ResetTarget() {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			glViewport(0, 0, width_, height_);
		}

        /**
         * @brief		�`��J�n
         */
        void RenderBegin();

        /**
         * @brief		�`��
         */
        void RenderEnd();

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