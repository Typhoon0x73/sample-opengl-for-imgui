#pragma once

#include	"Application.h"
#include    "Application/SpriteAnimation.h"
#include    "PrimitiveRenderUtilities.h"
#include    "imgui_internal.h"

using namespace Sample;

std::vector<TexturePtr> sampleTextures;
SpritePtr  sampleSprite;
std::vector<std::string> texturePathArray;
int editAnimNo = 0;
int editPatternNo = 0;

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
	frameCanvas_->Create(1024, 768);
	canvas_ = frameCanvas_->CreateSprite(GraphicsController::GetInstance().Shader());

	SpriteAnimation animation;
	animation.addPattern(SpriteAnimation::Pattern{ 0,   0, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0,  60, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 120, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 180, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 240, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 300, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 360, 0, 60, 64, 0.080, 0, 0 });
	animation.addPattern(SpriteAnimation::Pattern{ 0, 420, 0, 60, 64, 0.080, 0, 0 });
	animation.setLoop(true);
	test.addAnimation("idle", animation);

	sampleTextures.push_back(std::make_shared<Texture>("Player.png"));
	sampleSprite  = std::make_shared<Sprite>();
	sampleSprite->Create(sampleTextures[0], GraphicsController::GetInstance().Shader());

	texturePathArray.push_back("Player.png");

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
	test.changeAnimation("idle");
}

/**
 * @brief		更新
 */
void Application::Update() {
	//TODO:
	//アプリの更新処理を記述
	test.update(timer_->Time());
	auto ptn = test.currentPattern();
	if (ptn)
	{
		auto l = ptn->m_OffsetX;
		auto t = ptn->m_OffsetY;
		auto r = ptn->m_Width  + l;
		auto b = ptn->m_Height + t;

		sampleSprite->SrcRect(RectangleF(l, t, r, b));
		sampleSprite->Position(Vector3F(0.0f, 0.0f, 0.0f));
		sampleSprite->RefreshMatrix();

		std::cout << "{ " << ptn->m_ImageNo << ", ";
		std::cout << ptn->m_OffsetX << ", ";
		std::cout << ptn->m_OffsetY << ", ";
		std::cout << ptn->m_Width << ", ";
		std::cout << ptn->m_Height << ", ";
		std::cout << ptn->m_RefreshTime << ", ";
		std::cout << ptn->m_DrawOffsetX << ", ";
		std::cout << ptn->m_DrawOffsetY << ", ";
		std::cout << ptn->m_DrawOffsetY << " }\n";
	}
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
			auto tex = sampleTextures[0];
			ImVec2 size(tex->Width(), tex->Height());
			ImGui::Image((ImTextureID)tex->ID(), size);
			ImGui::SameLine();
			auto ptn = test.currentPattern();
			if (ptn)
			{
				auto scrollX = ImGui::GetScrollX();
				auto scrollY = ImGui::GetScrollY();
				auto padding = ImGui::GetStyle().WindowPadding;
				auto pos = ImGui::GetWindowPos();
				auto t = ImGui::GetCurrentContext()->CurrentWindow->TitleBarHeight();
				auto x = ptn->m_OffsetX + pos.x + padding.x - scrollX;
				auto y = ptn->m_OffsetY + pos.y + padding.y - scrollY + t;
				auto w = ptn->m_Width;
				auto h = ptn->m_Height;
				PrimitiveRenderUtilities::RenderRect(x, y, w, h, { 0.6f, 0.1f, 0.1f, 1.0f }, false);
			}
		}
		ImGui::End();

		ImGui::Begin("animations");
		{
			int current = editAnimNo;
			auto pAnimArray = test.animationArray();
			if (ImGui::BeginListBox("##animationList"))
			{
				if (pAnimArray)
				{
					auto listCount = pAnimArray->size();
					for (std::size_t i = 0; i < listCount; i++)
					{
						auto anim = pAnimArray->at(i);
						if (ImGui::Selectable(anim.first.c_str(), (i == current)))
						{
							test.changeAnimation(i);
							editAnimNo = i;
						}
					}
				}
				else
				{

				}
				ImGui::EndListBox();
			}
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

		ImGui::Begin("patterns");
		{
			auto ptns = test.animationArray()->at(editAnimNo).second.patternArray();
			if (!ptns)
			{

			}
			else
			{
				auto ptnCount = ptns->size();
				for (std::size_t i = 0; i < ptnCount; i++)
				{
					const auto& ptn = ptns->at(i);
					auto no  = ptn.m_ImageNo;
					if (no < 0)
					{
					}
					else
					{
						auto tex = sampleTextures[no];
						auto tw = (float)tex->Width();
						auto th = (float)tex->Height();
						ImVec2 uv0((float)ptn.m_OffsetX / tw, (float)ptn.m_OffsetY / th);
						ImVec2 uv1((float)(ptn.m_OffsetX + ptn.m_Width) / tw, (float)(ptn.m_OffsetY + ptn.m_Height) / th);
						ImTextureID id = (void*)tex->ID();
						auto w = (float)ptn.m_Width;
						auto h = (float)ptn.m_Height;
						if (ImGui::ImageButton(id, ImVec2(w, h), uv0, uv1))
						{
							editPatternNo = i;
							break;
						}
					}
					ImGui::SameLine();
				}
			}
		}
		ImGui::End();

		ImGui::Begin("animation view");
		{
			auto ptn = test.currentPattern();
			if (ptn)
			{
				auto x = ptn->m_OffsetX;
				auto y = ptn->m_OffsetY;
				auto w = ptn->m_Width;
				auto h = ptn->m_Height;
				auto tex = canvas_->Texture();
				ImVec2 size(tex->Width(), tex->Height());
				ImVec2 uv((float)w / (float)tex->Width(), (float)h / (float)tex->Height());
				ImGui::Image((ImTextureID)tex->ID(), ImVec2(w, h), ImVec2(0, 1), ImVec2(uv.x, 1.0f - uv.y));
			}
		}
		ImGui::End();

		ImGui::Begin("editor");
		{
			auto const pattern = test.animationArray()->at(editAnimNo).second.patternByArrayNo(editPatternNo);
			if (!pattern)
			{

			}
			else
			{
				auto imageNo = pattern->m_ImageNo;
				bool isValid = (imageNo >= 0) && (imageNo < texturePathArray.size());
				const char* const selectName = (isValid ? texturePathArray[imageNo].c_str() : "none");
				if (ImGui::BeginCombo("texture", selectName))
				{
					if (ImGui::Selectable("none", (imageNo == -1)))
					{
						pattern->m_ImageNo = -1;
					}
					auto texPathCount = texturePathArray.size();
					for (std::size_t i = 0; i < texPathCount; i++)
					{
						if (ImGui::Selectable(texturePathArray[i].c_str(), (i == imageNo)))
						{
							pattern->m_ImageNo = 0;
						}
					}
					ImGui::EndCombo();
				}
				auto offsetX = pattern->m_OffsetX;
				if (ImGui::InputInt("offset x", &offsetX))
				{
					pattern->m_OffsetX = offsetX;
				}
				auto offsetY = pattern->m_OffsetY;
				if (ImGui::InputInt("offset y", &offsetY))
				{
					pattern->m_OffsetY = offsetY;
				}
				auto width = pattern->m_Width;
				if (ImGui::InputInt("width", &width))
				{
					pattern->m_Width = width;
				}
				auto height = pattern->m_Height;
				if (ImGui::InputInt("height", &height))
				{
					pattern->m_Height = height;
				}
			}
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

		sampleSprite->Position(Vector3F(0.0f, 0.0f, 0.0f));
		sampleSprite->RefreshMatrix();
		sampleSprite->Render();
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