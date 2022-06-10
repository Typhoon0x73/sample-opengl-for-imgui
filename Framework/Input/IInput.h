#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class __declspec(novtable) IInput
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IInput() = default;

		/**
		 * @brief		���͂̍X�V
		 *				Framework::Run�ɂČĂяo��
		 */
		virtual void Refresh() = 0;

		/**
		 * @brief		�L�[��Ԃ̎擾
		 * @param[in]	keycode	�L�[�R�[�h
		 */
		virtual int GetKeyState(const int keycode) noexcept = 0;

		/**
		 * @brief		�}�E�X���ʒu
		 * @return		�}�E�X���ʒu
		 */
		virtual const double GetMouseX() const noexcept = 0;

		/**
		 * @brief		�}�E�X�c�ʒu
		 * @return		�}�E�X�c�ʒu
		 */
		virtual const double GetMouseY() const noexcept = 0;
	};
	using InputPtr = std::shared_ptr< IInput >;

}