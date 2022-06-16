#pragma once

#include	"Application.h"
#include    "Application/SpriteAnimation.h"
#include    "PrimitiveRenderUtilities.h"

using namespace Sample;

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

SpriteAnimationController test;
/**
 * @brief		初期化
 */
void Application::Initialize() {
	//リソースディレクトリを素材配置先に指定
	::SetCurrentDirectory(L"Resources");

	//TODO:
	//アプリの初期化処理を記述

	//カメラ設定
	camera_ = std::make_shared<Camera>();
	camera_->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera_);

	auto& imguiIO = ImGui::GetIO();
	imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	frameCanvas_ = std::make_shared<FrameBuffer>();
	frameCanvas_->Create(4096, 4096);
	canvas_ = frameCanvas_->CreateSprite(GraphicsController::GetInstance().Shader());

	SpriteAnimation animation;
	animation.addPattern(SpriteAnimation::Pattern{ 0,   0, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0,  32, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0,  64, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0,  96, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 128, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 160, 0, 32, 32, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 192, 0, 32, 32, 0.080, 0, 0 });
	animation.setLoop(true);
	test.addAnimation("sample", animation);

	std::vector<std::string> texturePathArray;
	texturePathArray.push_back("enemy.png");

	SpriteAnimationDataExporter exporter("sample.sa");
	if (!exporter.exportToSA(&test, &texturePathArray))
	{
		return;
	}

	std::vector<std::string> texturePathArray2;
	SpriteAnimationController test2("sample.sa", &texturePathArray2);
	if (test != test2)
	{
		return;
	}
	test.changeAnimation("sample");
}

/**
 * @brief		更新
 */
void Application::Update() {
	//TODO:
	//アプリの更新処理を記述
	test.update(timer_->Time() * 0.1f);
	std::cout << "{ " << test.currentPattern()->m_ImageNo << ", ";
	std::cout << test.currentPattern()->m_OffsetX     << ", ";
	std::cout << test.currentPattern()->m_OffsetY     << ", ";
	std::cout << test.currentPattern()->m_Width       << ", ";
	std::cout << test.currentPattern()->m_Height      << ", ";
	std::cout << test.currentPattern()->m_RefreshTime << ", ";
	std::cout << test.currentPattern()->m_DrawOffsetX << ", ";
	std::cout << test.currentPattern()->m_DrawOffsetY << ", ";
	std::cout << test.currentPattern()->m_DrawOffsetY << " }\n";
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

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("file"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("canvas", nullptr, ImGuiWindowFlags_NoBackground);
		{
			auto tex = canvas_->Texture();
			ImVec2 size(tex->Width(), tex->Height());
			ImGui::Image((ImTextureID)tex->ID(), size, ImVec2(0, 1), ImVec2(1, 0));
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
    ImGui::End();
    /*//**/
    //ImGui::ShowDemoWindow();
}

/**
 * @brief		描画
 */
void Application::Render() {

	// キャンバス用描画
	frameCanvas_->Bind();
	{
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		auto ptn = test.currentPattern();
		if (ptn)
		{
			PrimitiveRenderUtilities::RenderRect(
				ptn->m_OffsetX, ptn->m_OffsetY, ptn->m_Width, ptn->m_Height,
				Vector4F(1.0f, 1.0f, 1.0f, 1.0f), true
			);
		}
	}

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