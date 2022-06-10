#pragma once

#include	"IFrameTimer.h"

namespace Sample {

	/**
	 * @brief		フレーム時間計測
	 */
	class GLFrameTimer : public IFrameTimer
	{
	protected:
		/** フレーム時間 */
		float				frameTime_;
		/** 現在のフレーム時間 */
		double				currentFrameTime_;
		/** 開始時間 */
		double				prevTime_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		GLFrameTimer(int fps)
			: frameTime_(1.0f / fps)
			, currentFrameTime_(0) 
			, prevTime_(0) {
			glfwSetTime(0.0);
		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~GLFrameTimer() {
		}

		/**
		 * @brief		更新
		 */
		void Refresh() override {
			const double NowTime = glfwGetTime();
			currentFrameTime_ = NowTime - prevTime_;
			prevTime_ = NowTime;
		}

		/**
		 * @brief		一時停止
		 */
		void Sleep() override {
			if (currentFrameTime_ < frameTime_)
			{
				uint32_t t = static_cast<uint32_t>((frameTime_ - currentFrameTime_) * 1000);
				std::this_thread::sleep_for(std::chrono::milliseconds(t));
				currentFrameTime_ = frameTime_;
				prevTime_ = glfwGetTime();
			}
		}

		/**
		 * @brief		経過時間取得
		 */
		float Time() const noexcept override {
			return static_cast<float>(currentFrameTime_);
		}
	};

}