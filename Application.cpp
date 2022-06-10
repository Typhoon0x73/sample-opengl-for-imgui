#pragma once

#include	"Application.h"

using namespace Sample;

//�`��֘A
CameraPtr camera;

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

    //�J�����ݒ�
    camera = std::make_shared<Camera>();
    camera->Create2D(1024, 768);
    GraphicsController::GetInstance().Camera(camera);

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
    {
        ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
        ImGui::SetWindowSize(ImVec2{ (float)GraphicsController::GetInstance().ScreenWidth(), (float)GraphicsController::GetInstance().ScreenHeight() });
        ImGuiID  baseDockspace = ImGui::GetID("##BaseDockSpace");
        unsigned dockNodeFlags = ImGuiDockNodeFlags_None;
        dockNodeFlags |= ImGuiWindowFlags_NoBackground;
        ImGui::DockSpace(baseDockspace, ImVec2{ 0.0f, 0.0f }, dockNodeFlags);
    }
    ImGui::End();
    /*//**/
    //ImGui::ShowDemoWindow();

    ImGui::Begin("canvas");
    {

    }
    ImGui::End();

    ImGui::Begin("animations");
    {

    }
    ImGui::End();

    ImGui::Begin("tool bar");
    {

    }
    ImGui::End();

    ImGui::Begin("sprites");
    {

    }
    ImGui::End();

    ImGui::Begin("animation view");
    {

    }
    ImGui::End();

    ImGui::Begin("editor");
    {

    }
    ImGui::End();
}

/**
 * @brief		�`��
 */
void Application::Render() {

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
}