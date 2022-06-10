#include    "GraphicsController.h"
#include    "FrameBuffer.h"
#include    "Shader.h"
#include    "Sprite.h"

using namespace Sample;

/**
 * @brief		������
 */
void GraphicsController::Initialize(GLFWwindow * w)
{
    window_ = w;
    glfwGetWindowSize(w, &width_, &height_);

    //�V�F�[�_�[�ǂݍ���
    if (!shader_)
    {
        shader_ = std::make_shared<Shader>("Resources/Sprite.vert", "Resources/Sprite.frag");
    }
    CreateBuffer();
}

/**
 * @brief		�`��p�o�b�t�@�̐���
 */
void Sample::GraphicsController::CreateBuffer()
{
    if (frameBuffer_)
    {
        frameBuffer_->Release();
        frameBuffer_ = nullptr;
    }
    // ���ۂ̃E�B���h�E�T�C�Y (�s�N�Z����) ���擾
    int renderBufferWidth, renderBufferHeight;
    glfwGetFramebufferSize(window_, &renderBufferWidth, &renderBufferHeight);

    frameBuffer_ = std::make_shared<FrameBuffer>();
    frameBuffer_->Create(renderBufferWidth, renderBufferHeight);
    frameSprite_ = frameBuffer_->CreateSprite(shader_);
    if (currentCamera_)
    {
        currentCamera_->Create2D(renderBufferWidth, renderBufferHeight);
    }
}

/**
 * @brief		�`��J�n
 */
void GraphicsController::RenderBegin()
{
    //�t���[���o�b�t�@���p
    frameBuffer_->Bind();
}

/**
 * @brief		�`��
 */
void Sample::GraphicsController::RenderEnd()
{
    //��ʃN���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frameSprite_->Render();

    //��ʂɕ\��
    glfwSwapBuffers(window_);
}
