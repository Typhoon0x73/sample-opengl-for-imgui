#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class __declspec(novtable) IInput
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IInput() = default;

		/**
		 * @brief		入力の更新
		 *				Framework::Runにて呼び出し
		 */
		virtual void Refresh() = 0;

		/**
		 * @brief		キー状態の取得
		 * @param[in]	keycode	キーコード
		 */
		virtual int GetKeyState(const int keycode) noexcept = 0;

		/**
		 * @brief		マウス横位置
		 * @return		マウス横位置
		 */
		virtual const double GetMouseX() const noexcept = 0;

		/**
		 * @brief		マウス縦位置
		 * @return		マウス縦位置
		 */
		virtual const double GetMouseY() const noexcept = 0;
	};
	using InputPtr = std::shared_ptr< IInput >;

}