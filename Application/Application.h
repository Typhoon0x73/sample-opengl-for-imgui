#pragma once

#include	"../Framework/Framework/Framework.h"
#include    "../AnimakeData.h"
#include    "SpriteAnimation.h"

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

	private:

		//�`��֘A
		CameraPtr camera_;

		AnimakeDataPtr data_;
	};
}