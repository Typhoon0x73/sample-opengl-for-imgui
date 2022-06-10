#pragma once

#include	"Application.h"

using namespace Sample;

//�`��֘A
ShaderPtr shader;
CameraPtr camera;

FrameBufferPtr frameBuffer;
SpritePtr frameSprite;

/**
 * @brief		�R���X�g���N�^
 */
Application::Application()
: Framework() {
}

/**
 * @brief		�f�X�g���N�^
 */
Application::~Application() {
}

/**
 * @brief		������
 */
void Application::Initialize() {
    //���\�[�X�f�B���N�g����f�ޔz�u��Ɏw��
    ::SetCurrentDirectory(L"Resources");

    //TODO:
    //�A�v���̏������������L�q

    //�V�F�[�_�[�ǂݍ���
    shader = std::make_shared<Shader>("Sprite.vert", "Sprite.frag");

    //�J�����ݒ�
    camera = std::make_shared<Camera>();
    camera->Create2D(1024, 768);
    GraphicsController::GetInstance().Camera(camera);

    //�t���[���o�b�t�@����
    frameBuffer = std::make_shared<FrameBuffer>();
    frameBuffer->Create(GraphicsController::GetInstance().ScreenWidth(),
        GraphicsController::GetInstance().ScreenHeight());
    frameSprite = frameBuffer->CreateSprite(shader);

    auto& imguiIO = ImGui::GetIO();
    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

/**
 * @brief		�X�V
 */
void Application::Update() {
	//TODO:
	//�A�v���̍X�V�������L�q

    /**/
    unsigned flags = ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_MenuBar;
    ImGui::Begin("##BaseWindowDockSpace", nullptr, flags);
    ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
    ImGui::SetWindowSize(ImVec2{ (float)Framework::width_, (float)Framework::height_ });
    ImGuiID baseDockspace = ImGui::GetID("##BaseDockSpace");
    unsigned dockNodeFlags = ImGuiDockNodeFlags_None;
    dockNodeFlags |= ImGuiWindowFlags_NoBackground;
    ImGui::DockSpace(baseDockspace, ImVec2{ 0.0f, 0.0f }, dockNodeFlags);
    ImGui::End();
    /*//**/
    ImGui::ShowDemoWindow();
}

/**
 * @brief		�`��
 */
void Application::Render() {
    //�t���[���o�b�t�@���p
    frameBuffer->Bind();

    //�����ݒ�Ɖ�ʃN���A
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //TODO:
    //�A�v���̕`�揈�����L�q


    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //�^�[�Q�b�g�̃��Z�b�g
    GraphicsController::GetInstance().ResetTarget();

    //��ʃN���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frameSprite->Render();

    //��ʂɕ\��
    glfwSwapBuffers(window_);
    glfwPollEvents();
}