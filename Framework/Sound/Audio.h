#pragma once

#include	"IAudio.h"

namespace Sample {

	class Audio : public IAudio
	{
	private:
		/** ALデバイス */
		ALCdevice*					alDevice_;
		/** ALコンテキスト */
		ALCcontext*					alContext_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Audio()
			: alDevice_(nullptr)
			, alContext_(nullptr) {
		}
		/**
		 * @brief		デストラクタ
		 */
		virtual ~Audio() {
			Release();
		}

		/**
		 * @brief		OpenALの初期化
		 * @return		true	生成成功
		 *				false	生成失敗
		 */
		bool Initialize() override;

		/**
		 * @brief		解放処理
		 */
		void Release() override;

		/**
		 * @brief		距離モデル設定
		 */
		void DistanceModel(ALenum en);
		/**
		 * @brief		ドップラー設定
		 */
		void DopplerFactor(ALfloat v);
		/**
		 * @brief		ドップラー速度設定
		 */
		void DopplerVelocity(ALfloat v);

		/**
		 * @brief		各種取得のみのメソッド
		 */
		ALCdevice* Device() { return alDevice_; }
		ALCcontext* Ccontext() { return alContext_; }
	};
}