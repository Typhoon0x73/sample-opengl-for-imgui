#pragma once

#include	"../Framework/Framework/Framework.h"
#include    "../AnimakeData.h"
#include    "SpriteAnimation.h"

namespace Sample {

	class Application : public Framework {
	public:

		/**
		 * @brief		コンストラクタ
		 */
		Application();

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Application();
	protected:
		/**
		 * @brief		初期化
		 */
		void Initialize() override;

		/**
		 * @brief		更新
		 */
		void Update() override;

		/**
		 * @brief		描画
		 */
		void Render() override;

	private:

		//描画関連
		CameraPtr camera_;

		AnimakeDataPtr data_;
	};
}