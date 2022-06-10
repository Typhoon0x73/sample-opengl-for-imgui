#pragma once

#include	"../Resource/ResourceBase.h"
#include	"WaveFile.h"

namespace Sample {

	/**
	 * @brief		音ファイルを扱うためのクラス
	 */
	class Sound : public ResourceBase
	{
	protected:
		/** バッファ */
		ALuint			buffer_;
		/** ソース */
		ALuint			source_;
		/** Waveファイル */
		WaveFilePtr		wave_;

		/**
		 * @brief		バッファのフォーマット判定
		 */
		unsigned long BufferFormat();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Sound();

		/**
		 * @brief		コンストラクタ
		 *				生成と同時に読み込みをおこなう
		 * @param[in]	name	読み込むサウンド名
		 */
		Sound(const char* name);

		/**
		 * @brief		デストラクタ
		 */
		virtual ~Sound();

		/**
		 * @brief		読み込み
		 * @param[in]	name	読み込むサウンド名
		 * @return		true	読み込み成功
		 *				false	読み込み失敗
		 */
		bool Load(const char* name);

		/**
		 * @brief		再生
		 */
		void Play();

		/**
		 * @brief		停止
		 */
		void Stop();

		/**
		 * @brief		解放処理
		 */
		void Release();

		/**
		 * @brief		ループ設定
		 * @param[in]	p	ループフラグ(AL_TRUE：ループあり、AL_FALSE:：ループ無し)
		 */
		void Loop(const ALint& p);

		/**
		 * @brief		各種取得のみのメソッド
		 */
		const ALuint Buffer() const { return buffer_; }
		const ALuint Source() const { return source_; }
	};
	using SoundPtr = std::shared_ptr< Sound >;
	using SoundArray = std::vector< SoundPtr >;

}