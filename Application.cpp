#pragma once

#include	"Application.h"
#include    "Application/SpriteAnimation.h"
#include    "PrimitiveRenderUtilities.h"
#include    "imgui_internal.h"

using namespace Sample;

std::vector<TexturePtr>  sampleTextures;
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

spa::SpriteAnimationController test;
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
	test.addAnimation("idle", animation);

	sampleTextures.push_back(std::make_shared<Texture>("Player.png"));

	texturePathArray.push_back("Player.png");

	spa::SpriteAnimationDataExporter exporter("sample.spa");
	if (!exporter.exportToSA(&test, &texturePathArray))
	{
		return;
	}

	std::vector<std::string> texturePathArray2;
	spa::SpriteAnimationController test2("sample.spa", &texturePathArray2);
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
				for (const auto& layer : ptn->m_LayerArray)
				{
					const auto& scrollX = ImGui::GetScrollX();
					const auto& scrollY = ImGui::GetScrollY();
					const auto& padding = ImGui::GetStyle().WindowPadding;
					const auto& pos     = ImGui::GetWindowPos();
					const auto& t       = ImGui::GetCurrentContext()->CurrentWindow->TitleBarHeight();
					const auto& x       = layer.second.m_OffsetX + pos.x + padding.x - scrollX;
					const auto& y       = layer.second.m_OffsetY + pos.y + padding.y - scrollY + t;
					const auto& w       = layer.second.m_Width;
					const auto& h       = layer.second.m_Height;
					PrimitiveRenderUtilities::RenderRect(x, y, w, h, { 0.6f, 0.1f, 0.1f, 1.0f }, false);
				}
			}
		}
		ImGui::End();

		ImGui::Begin("texture view");
		{

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

		ImGui::Begin("textures");
		{

		}
		ImGui::End();

		ImGui::Begin("patterns", nullptr, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
		{
			const auto const anims = test.animationArray();
			const auto const ptns = anims->at(editAnimNo).second.patternArray();
			if (!ptns)
			{

			}
			else
			{
				/*auto ptnCount = ptns->size();
				for (std::size_t i = 0; i < ptnCount; i++)
				{
					const auto& ptn = ptns->at(i);
					const auto& no  = ptn.m_ImageNo;
					if (no < 0)
					{
						if (ImGui::Button("no image"))
						{
							editPatternNo = i;
							break;
						}
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
						ImVec2 padding = ImGui::GetStyle().FramePadding;
						ImVec4 bgColor = ((i == editPatternNo) ? ImGui::GetStyle().Colors[ImGuiCol_Button] : ImVec4{ 0, 0, 0, 0 });
						ImVec4 tintColor{ 1.0f, 1.0f, 1.0f, 1.0f };
						auto btnId = "##ptn_id_" + std::to_string(i);
						if (ImGui::ImageButtonEx(ImGui::GetID(btnId.c_str()), id, ImVec2(w, h), uv0, uv1, padding, bgColor, tintColor))
						{
							editPatternNo = i;
							break;
						}
					}
					ImGui::SameLine();
				}*/
			}
		}
		ImGui::End();

		ImGui::Begin("animation view");
		{
			auto ptn = test.currentPattern();
			if (ptn)
			{
				for (const auto& layer : ptn->m_LayerArray)
				{
					const auto& imageNo = layer.second.m_ImageNo;
					if(imageNo < 0)
					{
						continue;
					}
					const auto& x = layer.second.m_OffsetX;
					const auto& y = layer.second.m_OffsetY;
					const auto& w = layer.second.m_Width;
					const auto& h = layer.second.m_Height;
					const auto& tex = sampleTextures[imageNo];
					ImVec2 size(tex->Width(), tex->Height());
					ImVec2 uv0((float)(x) / (float)tex->Width(), (float)(y) / (float)tex->Height());
					ImVec2 uv1((float)(x + w) / (float)tex->Width(), (float)(y + h) / (float)tex->Height());
					ImGui::Image((ImTextureID)tex->ID(), ImVec2(w, h), uv0, uv1);
				}
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
				/*auto imageNo = pattern->m_ImageNo;
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
				if (ImGui::DragInt("offset x", &offsetX))
				{
					pattern->m_OffsetX = offsetX;
				}
				auto offsetY = pattern->m_OffsetY;
				if (ImGui::DragInt("offset y", &offsetY))
				{
					pattern->m_OffsetY = offsetY;
				}
				auto width = pattern->m_Width;
				if (ImGui::DragInt("width", &width))
				{
					pattern->m_Width = width;
				}
				auto height = pattern->m_Height;
				if (ImGui::DragInt("height", &height))
				{
					pattern->m_Height = height;
				}
				float refresh = static_cast<float>(pattern->m_RefreshTime);
				if (ImGui::DragFloat("refresh", &refresh, 0.004f, 0.0f, 100.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
				{
					pattern->m_RefreshTime = static_cast<double>(refresh);
				}
				auto drawOffsetX = pattern->m_DrawOffsetX;
				if (ImGui::DragInt("draw offset x", &drawOffsetX))
				{
					pattern->m_DrawOffsetX = drawOffsetX;
				}
				auto drawOffsetY = pattern->m_DrawOffsetY;
				if (ImGui::DragInt("draw offset y", &drawOffsetY))
				{
					pattern->m_DrawOffsetY = drawOffsetY;
				}*/
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