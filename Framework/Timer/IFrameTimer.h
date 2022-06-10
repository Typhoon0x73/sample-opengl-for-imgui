#pragma once

#include	"../Common/Common.h"

namespace Sample {

	/**
	 * @brief		�t���[�����Ԍv��
	 */
	class __declspec(novtable) IFrameTimer
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IFrameTimer() = default;

		/**
		 * @brief		�X�V
		 */
		virtual void Refresh() = 0;

		/**
		 * @brief		�ꎞ��~
		 */
		virtual void Sleep() = 0;

		/**
		 * @brief		�o�ߎ��Ԏ擾
		 */
		virtual float Time() const noexcept = 0;
	};
	//�|�C���^�u������
	using FrameTimerPtr = std::shared_ptr<IFrameTimer>;

}