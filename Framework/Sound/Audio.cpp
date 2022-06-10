#include	"Audio.h"

using namespace Sample;

/**
 * @brief		OpenALの初期化
 * @return		true	生成成功
 *				false	生成失敗
 */
bool Audio::Initialize() {
	alDevice_ = alcOpenDevice(0);
	alContext_ = alcCreateContext(alDevice_, NULL);
	alcMakeContextCurrent(alContext_);
	INFO_LOG("OpenALの初期化...");
	return true;
}

/**
 * @brief		解放処理
 */
void Audio::Release() {
	if (alContext_ == nullptr || alDevice_ == nullptr)
	{
		return;
	}
	alcMakeContextCurrent(NULL);
	alcDestroyContext(alContext_);
	alcCloseDevice(alDevice_);
	alDevice_ = nullptr;
	alContext_ = nullptr;
	INFO_LOG("OpenALの解放...");
}

/**
 * @brief		距離モデル設定
 */
void Audio::DistanceModel(ALenum en) {
	alDistanceModel(en);
}
/**
 * @brief		ドップラー設定
 */
void Audio::DopplerFactor(ALfloat v) {
	alDopplerFactor(v);
}
/**
 * @brief		ドップラー速度設定
 */
void Audio::DopplerVelocity(ALfloat v) {
	alDopplerVelocity(v);
}