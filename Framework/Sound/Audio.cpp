#include	"Audio.h"

using namespace Sample;

/**
 * @brief		OpenAL�̏�����
 * @return		true	��������
 *				false	�������s
 */
bool Audio::Initialize() {
	alDevice_ = alcOpenDevice(0);
	alContext_ = alcCreateContext(alDevice_, NULL);
	alcMakeContextCurrent(alContext_);
	INFO_LOG("OpenAL�̏�����...");
	return true;
}

/**
 * @brief		�������
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
	INFO_LOG("OpenAL�̉��...");
}

/**
 * @brief		�������f���ݒ�
 */
void Audio::DistanceModel(ALenum en) {
	alDistanceModel(en);
}
/**
 * @brief		�h�b�v���[�ݒ�
 */
void Audio::DopplerFactor(ALfloat v) {
	alDopplerFactor(v);
}
/**
 * @brief		�h�b�v���[���x�ݒ�
 */
void Audio::DopplerVelocity(ALfloat v) {
	alDopplerVelocity(v);
}