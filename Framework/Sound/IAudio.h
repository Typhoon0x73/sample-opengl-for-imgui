#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class __declspec(novtable) IAudio
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IAudio() = default;

		/**
		 * @brief		OpenAL�̏�����
		 * @return		true	��������
		 *				false	�������s
		 */
		virtual bool Initialize() = 0;

		/**
		 * @brief		�������
		 */
		virtual void Release() = 0;
	};
	using AudioPtr = std::shared_ptr< IAudio >;
}