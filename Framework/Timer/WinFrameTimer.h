#pragma once

#include	"IFrameTimer.h"

namespace Sample {

	/**
	 * @brief		フレーム時間計測
	 */
	class WinFrameTimer : public IFrameTimer
	{
	protected:
		/** フレーム時間 */
		float				frameTime_;
		/** 現在のフレーム時間 */
		float				currentFrameTime_;
		/** 開始時間 */
		LARGE_INTEGER		prevTime_;
		/** 周波数 */
		LARGE_INTEGER		timeFreq_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		WinFrameTimer(int fps)
			: frameTime_(1.0f / fps)
			, currentFrameTime_(0) 
			, prevTime_()
			, timeFreq_() {
			//周波数
			QueryPerformanceFrequency(&timeFreq_);
			//1度取得しておく(初回計算用)
			QueryPerformanceCounter(&prevTime_);
			//タイマーの分解機能をあげる
			timeBeginPeriod(1);
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~WinFrameTimer() {
			timeEndPeriod(1);
		}

		/**
		 * @brief		更新
		 */
		void Refresh() override {
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			currentFrameTime_ = static_cast<float>(now.QuadPart - prevTime_.QuadPart) / static_cast<float>(timeFreq_.QuadPart);
			prevTime_ = now;
		}

		/**
		 * @brief		一時停止
		 */
		void Sleep() override {
			if (currentFrameTime_ < frameTime_)
			{
				LARGE_INTEGER now;
				DWORD t = static_cast<DWORD>((frameTime_ - currentFrameTime_) * 1000);
				std::this_thread::sleep_for(std::chrono::milliseconds(t));
				currentFrameTime_ = frameTime_;
				QueryPerformanceCounter(&now);
				prevTime_ = now;
			}
		}

		/**
		 * @brief		経過時間取得
		 */
		float Time() const noexcept override {
			return currentFrameTime_;
		}
	};

}