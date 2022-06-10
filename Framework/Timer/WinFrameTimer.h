#pragma once

#include	"IFrameTimer.h"

namespace Sample {

	/**
	 * @brief		�t���[�����Ԍv��
	 */
	class WinFrameTimer : public IFrameTimer
	{
	protected:
		/** �t���[������ */
		float				frameTime_;
		/** ���݂̃t���[������ */
		float				currentFrameTime_;
		/** �J�n���� */
		LARGE_INTEGER		prevTime_;
		/** ���g�� */
		LARGE_INTEGER		timeFreq_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		WinFrameTimer(int fps)
			: frameTime_(1.0f / fps)
			, currentFrameTime_(0) 
			, prevTime_()
			, timeFreq_() {
			//���g��
			QueryPerformanceFrequency(&timeFreq_);
			//1�x�擾���Ă���(����v�Z�p)
			QueryPerformanceCounter(&prevTime_);
			//�^�C�}�[�̕����@�\��������
			timeBeginPeriod(1);
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~WinFrameTimer() {
			timeEndPeriod(1);
		}

		/**
		 * @brief		�X�V
		 */
		void Refresh() override {
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			currentFrameTime_ = static_cast<float>(now.QuadPart - prevTime_.QuadPart) / static_cast<float>(timeFreq_.QuadPart);
			prevTime_ = now;
		}

		/**
		 * @brief		�ꎞ��~
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
		 * @brief		�o�ߎ��Ԏ擾
		 */
		float Time() const noexcept override {
			return currentFrameTime_;
		}
	};

}