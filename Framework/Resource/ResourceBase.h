#pragma once

#include	"../Common/Common.h"

namespace Sample {

	class ResourceBase
	{
	protected:
		/** ���O */
		std::string		name_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		ResourceBase() :
		name_() {
		}
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ResourceBase() {
		}

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const std::string& Name() const noexcept { return name_; }
	};

}