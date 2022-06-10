#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class __declspec(novtable) IAudio
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IAudio() = default;

		/**
		 * @brief		OpenALの初期化
		 * @return		true	生成成功
		 *				false	生成失敗
		 */
		virtual bool Initialize() = 0;

		/**
		 * @brief		解放処理
		 */
		virtual void Release() = 0;
	};
	using AudioPtr = std::shared_ptr< IAudio >;
}