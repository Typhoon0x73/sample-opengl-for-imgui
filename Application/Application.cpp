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
#include    "widgets/PatternListWidget.h"
#include    "widgets/TextureListWidget.h"
#include    "widgets/TextureView.h"

using namespace Sample;

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
	g_pGetBlackboard(AnimakeData*)->erase("AnimakeData");
	g_BlackboardRelease(AnimakeData*);
}

/**
 * @brief		������
 */
void Application::Initialize() {
	//���\�[�X�f�B���N�g����f�ޔz�u��Ɏw��
	::SetCurrentDirectory(L"Resources");

	//TODO:
	//�A�v���̏������������L�q

	if (data_ == nullptr)
	{
		data_ = new AnimakeData();
	}

	//�J�����ݒ�
	camera_ = std::make_shared<Camera>();
	camera_->Create2D(1024, 768);
	GraphicsController::GetInstance().Camera(camera_);

	auto& imguiIO = ImGui::GetIO();
	imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	spa::SpriteAnimation animation;
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0,   0, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0,  60, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 120, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 180, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 240, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 300, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 360, 0, 60, 64, 0, 0 })), 0.080 });
	animation.addPattern(spa::Pattern{ spa::LayerArray(1, spa::LayerData( "0", spa::Layer{ 0, 420, 0, 60, 64, 0, 0 })), 0.080 });
	animation.setLoop(true);
	data_->m_SpriteAnimation.addAnimation("idle", animation);

	data_->m_SampleTextures.push_back(std::make_shared<Texture>("Player.png"));

	data_->m_TexturePathArray.push_back("Player.png");

	spa::SpriteAnimationDataExporter exporter("sample.spa");
	if (!exporter.exportToSA(&data_->m_SpriteAnimation, &data_->m_TexturePathArray))
	{
		return;
	}

	std::vector<std::string> texturePathArray2;
	spa::SpriteAnimationController test2("sample.spa", &texturePathArray2);
	if (data_->m_SpriteAnimation != test2)
	{
		return;
	}
	data_->m_SpriteAnimation.changeAnimation("idle");
	g_pGetBlackboard(AnimakeData*)->add("AnimakeData", data_);

	// Widgets
	WidgetManager::GetInstance().regist(std::move(std::make_unique< AnimationListWidget >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< AnimationView       >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< CanvasWidget        >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< EditorWidget        >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< MainMenuBar         >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< PatternListWidget   >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< TextureListWidget   >()));
	WidgetManager::GetInstance().regist(std::move(std::make_unique< TextureView         >()));
}

/**
 * @brief		�X�V
 */
void Application::Update() {
	//TODO:
	//�A�v���̍X�V�������L�q

	data_->m_SpriteAnimation.update(timer_->Time());

    
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

		ImGui::Begin("tool bar");
		{

		}
		ImGui::End();

	}
    ImGui::End();

    /*//**/
    //ImGui::ShowDemoWindow();
}

/**
 * @brief		�`��
 */
void Application::Render() {

	// �ʏ�`��
	//�t���[���o�b�t�@���p
	GraphicsController::GetInstance().FrameBuffer()->Bind();
	{
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
	}


    //�^�[�Q�b�g�̃��Z�b�g
    GraphicsController::GetInstance().ResetTarget();
}