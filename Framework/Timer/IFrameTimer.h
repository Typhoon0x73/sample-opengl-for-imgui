#pragma once

#include	"../Common/Common.h"

namespace Sample {

	/**
	 * @brief		フレーム時間計測
	 */
	class __declspec(novtable) IFrameTimer
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IFrameTimer() = default;

		/**
		 * @brief		更新
		 */
		virtual void Refresh() = 0;

		/**
		 * @brief		一時停止
		 */
		virtual void Sleep() = 0;

		/**
		 * @brief		経過時間取得
		 */
		virtual float Time() const noexcept = 0;
	};
	//ポインタ置き換え
	using FrameTimerPtr = std::shared_ptr<IFrameTimer>;

}