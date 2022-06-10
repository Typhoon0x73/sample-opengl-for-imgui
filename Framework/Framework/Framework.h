#pragma once

#include	"../Timer/GLFrameTimer.h"
#include	"../Sound/Audio.h"
#include	"../Sound/Sound.h"
#include	"../Input/Input.h"
#include	"../Graphics/Sprite.h"
#include	"../Graphics/SpriteBatch.h"
#include	"../Graphics/FontRender.h"
#include	"../Graphics/PolyLine.h"
#include	"../Graphics/FrameBuffer.h"
#include	"../Graphics/ShaderParameterBind1F.h"
#include	"../Graphics/GraphicsController.h"
#include    "imgui.h"
#include    "imgui_impl_glfw.h"
#include    "imgui_impl_opengl3.h"

namespace Sample {

	class Framework
	{
	protected:
		/** GL�E�C���h�E */
		GLFWwindow*		window_;

		/** �^�C�}�[ */
		FrameTimerPtr	timer_;

		/** �I�[�f�B�I�f�o�C�X */
		AudioPtr		audio_;

		/** ���̓f�o�C�X */
		InputPtr		input_;

		/** �E�C���h�E�̕� */
		int				width_;

		/** �E�C���h�E�̍��� */
		int				height_;

		/**
		 * @brief		������
		 */
		virtual void Initialize() = 0;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() = 0;

		/**
		 * @brief		�`��
		 */
		virtual void Render() = 0;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Framework();

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Framework();

		/**
		 * @brief		�t���[�����[�N�̐���
		 * @param[in]	w		��ʂ̕�
		 * @param[in]	h		��ʂ̍���
		 * @param[in]	title	�E�C���h�E�^�C�g��
		 */
		virtual bool Create(int w, int h, const char* title);

		/**
		 * @brief		�t���[�����[�N�̎��s
		 */
		virtual void Run();
	};

}