#include    "GraphicsController.h"
#include    "FrameBuffer.h"
#include    "Shader.h"
#include    "Sprite.h"

using namespace Sample;

/**
 * @brief		初期化
 */
void GraphicsController::Initialize(GLFWwindow * w)
{
    window_ = w;
    glfwGetWindowSize(w, &width_, &height_);

    //シェーダー読み込み
    if (!shader_)
    {
        shader_ = std::make_shared<Sample::Shader>("Resources/Sprite.vert", "Resources/Sprite.frag");
    }
    CreateBuffer();
}

/**
 * @brief		描画用バッファの生成
 */
void Sample::GraphicsController::CreateBuffer()
{
    if (frameBuffer_)
    {
        frameBuffer_->Release();
        frameBuffer_ = nullptr;
    }
    // 実際のウィンドウサイズ (ピクセル数) を取得
    int renderBufferWidth, renderBufferHeight;
    glfwGetFramebufferSize(window_, &renderBufferWidth, &renderBufferHeight);

    frameBuffer_ = std::make_shared<Sample::FrameBuffer>();
    frameBuffer_->Create(renderBufferWidth, renderBufferHeight);
    frameSprite_ = frameBuffer_->CreateSprite(shader_);
    if (currentCamera_)
    {
        currentCamera_->Create2D(renderBufferWidth, renderBufferHeight);
    }
}

/**
 * @brief		描画開始
 */
void GraphicsController::RenderBegin()
{
}

/**
 * @brief		描画
 */
void Sample::GraphicsController::RenderEnd()
{
    //画面クリア
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frameSprite_->Render();

    //画面に表示
    glfwSwapBuffers(window_);
}
