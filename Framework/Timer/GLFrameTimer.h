#pragma once

#include	"IFrameTimer.h"

namespace Sample {

	/**
	 * @brief		�t���[�����Ԍv��
	 */
	class GLFrameTimer : public IFrameTimer
	{
	protected:
		/** �t���[������ */
		float				frameTime_;
		/** ���݂̃t���[������ */
		double				currentFrameTime_;
		/** �J�n���� */
		double				prevTime_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		GLFrameTimer(int fps)
			: frameTime_(1.0f / fps)
			, currentFrameTime_(0) 
			, prevTime_(0) {
			glfwSetTime(0.0);
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~GLFrameTimer() {
		}

		/**
		 * @brief		�X�V
		 */
		void Refresh() override {
			const double NowTime = glfwGetTime();
			currentFrameTime_ = NowTime - prevTime_;
			prevTime_ = NowTime;
		}

		/**
		 * @brief		�ꎞ��~
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
		 * @brief		�o�ߎ��Ԏ擾
		 */
		float Time() const noexcept override {
			return static_cast<float>(currentFrameTime_);
		}
	};

}