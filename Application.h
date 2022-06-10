#pragma once

#include	"Framework/Framework/Framework.h"

namespace Sample {

	class Application : public Framework {
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Application();

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Application();
	protected:
		/**
		 * @brief		������
		 */
		void Initialize() override;

		/**
		 * @brief		�X�V
		 */
		void Update() override;

		/**
		 * @brief		�`��
		 */
		void Render() override;
	};
}