#pragma once

#include	"Application.h"

using namespace Sample;

//描画関連
CameraPtr camera;

/**
 * @brief		コンストラクタ
 */
Application::Application()
: Framework() {
}

/**
 * @brief		デストラクタ
 */
Application::~Application() {
}

/**
 * @brief		初期化
 */
void Application::Initialize() {
    //リソースディレクトリを素材配置先に指定
    ::SetCurrentDirectory(L"Resources");

    //TODO:
    //アプリの初期化処理を記述

    //カメラ設定
    camera = std::make_shared<Camera>();
    camera->Create2D(1024, 768);
    GraphicsController::GetInstance().Camera(camera);

    auto& imguiIO = ImGui::GetIO();
    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

/**
 * @brief		更新
 */
void Application::Update() {
	//TODO:
	//アプリの更新処理を記述

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
 * @brief		描画
 */
void Application::Render() {

    //初期設定と画面クリア
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //TODO:
    //アプリの描画処理を記述


    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //ターゲットのリセット
    GraphicsController::GetInstance().ResetTarget();
}