#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class ResourceBase
	{
	protected:
		/** 名前 */
		std::string		name_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		ResourceBase() :
		name_() {
		}
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ResourceBase() {
		}

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const std::string& Name() const noexcept { return name_; }
	};

}