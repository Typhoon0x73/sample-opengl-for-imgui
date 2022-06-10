#pragma once

#include	"../Timer/GLFrameTimer.h"
#include	"../Sound/Audio.h"
#include	"../Sound/Sound.h"
#include	"../Input/Input.h"
#include	"../Graphics/Sprite.h"
#include	"../Graphics/SpriteBatch.h"
#include	"../Graphics/FontRender.h"
#include	"../Graphics/PolyLine.h"
#include	"../Graphics/FrameBuffer.h"
#include	"../Graphics/ShaderParameterBind1F.h"
#include	"../Graphics/GraphicsController.h"
#include    "imgui.h"
#include    "imgui_impl_glfw.h"
#include    "imgui_impl_opengl3.h"

namespace Sample {

	class Framework
	{
	protected:
		/** GLウインドウ */
		GLFWwindow*		window_;

		/** タイマー */
		FrameTimerPtr	timer_;

		/** オーディオデバイス */
		AudioPtr		audio_;

		/** 入力デバイス */
		InputPtr		input_;

		/** ウインドウの幅 */
		int				width_;

		/** ウインドウの高さ */
		int				height_;

		/**
		 * @brief		初期化
		 */
		virtual void Initialize() = 0;

		/**
		 * @brief		更新
		 */
		virtual void Update() = 0;

		/**
		 * @brief		描画
		 */
		virtual void Render() = 0;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Framework();

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Framework();

		/**
		 * @brief		フレームワークの生成
		 * @param[in]	w		画面の幅
		 * @param[in]	h		画面の高さ
		 * @param[in]	title	ウインドウタイトル
		 */
		virtual bool Create(int w, int h, const char* title);

		/**
		 * @brief		フレームワークの実行
		 */
		virtual void Run();
	};

}