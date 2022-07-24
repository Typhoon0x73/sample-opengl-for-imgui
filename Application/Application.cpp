#pragma once

#include	"Application.h"
#include    "../PrimitiveRenderUtilities.h"
#include    "Blackboard/SingletonBlackboard.h"
#include    "imgui_internal.h"
#include    "widgets/WidgetManager.h"
#include    "widgets/AnimationListWidget.h"
#include    "widgets/AnimationView.h"
#include    "widgets/CanvasWidget.h"
#include    "widgets/EditorWidget.h"
#include    "widgets/MainMenuBar.h"
#include    "widgets/MainToolBar.h"
#include    "widgets/PatternListWidget.h"
#include    "widgets/TextureListWidget.h"
#include    "widgets/TextureView.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
Application::Application()
: Framework()
, animakeData_(nullptr) {
}

/**
 * @brief		デストラクタ
 */
Application::~Application() {
	g_pGetBlackboard(AnimakeDataPtr&)->erase("AnimakeData");
	g_BlackboardRelease(AnimakeDataPtr&);
}

/**
 * @brief		初期化
 */
void Application::Initialize() {
	//リソースディレクトリを素材配置先に指定
	::SetCurrentDirectory(L"Resources");

	animakeData_.reset(new AnimakeData);
	animakeData_->m_CurrentPath = wide_to_sjis(std::filesystem::current_path().native());

	//TODO:
	//アプリの初期化処理を記述
  
	//カメラ設定
	camera_ = std::make_shared<Camera>();
	camera_->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera_);

	auto& imguiIO = ImGui::GetIO();
	imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	spa::SpriteAnimation animation;
	spa::SpriteAnimation animation2;
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base1", spa::Layer{ 0,   0, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base2", spa::Layer{ 0,  60, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base3", spa::Layer{ 0, 120, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base4", spa::Layer{ 0, 180, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base5", spa::Layer{ 0, 240, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base6", spa::Layer{ 0, 300, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base7", spa::Layer{ 0, 360, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "base8", spa::Layer{ 0, 420, 0, 60, 64, 0, 0 })), 0.080 });
	animation.setLoop(true);
	animakeData_->m_SpriteAnimation.addAnimation("idle", animation);
	animakeData_->m_SpriteAnimation.addAnimation("idle2", animation2);

	animakeData_->m_SampleTextures.push_back(std::make_shared<Texture>("Player.png"));

	animakeData_->m_TexturePathArray.push_back("Player.png");

	spa::SpriteAnimationDataExporter exporter("sample.spa");
	if (!exporter.exportToSA(&animakeData_->m_SpriteAnimation, &animakeData_->m_TexturePathArray))
	{
		return;
	}

	std::vector<std::string> texturePathArray2;
	spa::SpriteAnimationController test2("sample.spa", &texturePathArray2);
	if (animakeData_->m_SpriteAnimation != test2)
	{
		return;
	}
  
	animakeData_->m_SpriteAnimation.changeAnimation("idle");
	g_pGetBlackboard(AnimakeDataPtr&)->add("AnimakeData", animakeData_);

	// Widgets
	WidgetManager::GetInstance().regist(std::move(std::make_unique< MainMenuBar         >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< MainToolBar         >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< TextureListWidget   >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< AnimationListWidget >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< PatternListWidget   >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< CanvasWidget        >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< EditorWidget        >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< TextureView         >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< AnimationView       >()));
}

/**
 * @brief		更新
 */
void Application::Update() {
	//TODO:
	//アプリの更新処理を記述

	animakeData_->m_SpriteAnimation.update(timer_->Time());

    
	/**/
    unsigned flags = ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_MenuBar;
	// DOCK
    ImGui::Begin("##BaseWindowDockSpace", nullptr, flags);
    {
        ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
        ImGui::SetWindowSize(ImVec2{ (float)GraphicsController::GetInstance().ScreenWidth(), (float)GraphicsController::GetInstance().ScreenHeight() });
        ImGuiID  baseDockspace = ImGui::GetID("##BaseDockSpace");
        unsigned dockNodeFlags = ImGuiDockNodeFlags_None;
        dockNodeFlags |= ImGuiWindowFlags_NoBackground;
        ImGui::DockSpace(baseDockspace, ImVec2{ 0.0f, 0.0f }, dockNodeFlags);

		// Widgets
		WidgetManager::GetInstance().update();

	}
    ImGui::End();

    /*//**/
	//ImGui::ShowDemoWindow();
}

/**
 * @brief		描画
 */
void Application::Render() {

	// 通常描画
	//フレームバッファ利用
	GraphicsController::GetInstance().FrameBuffer()->Bind();
	{
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
	}


    //ターゲットのリセット
    GraphicsController::GetInstance().ResetTarget();
}