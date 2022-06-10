#include	"Sound.h"

using namespace Sample;

/**
 * @brief		�R���X�g���N�^
 */
Sound::Sound()
: ResourceBase()
, buffer_(0)
, source_(0)
, wave_() {
}

/**
 * @brief		�R���X�g���N�^
 *				�����Ɠ����ɓǂݍ��݂������Ȃ�
 * @param[in]	name	�ǂݍ��ރe�N�X�`����
 */
Sound::Sound(const char* name)
: ResourceBase()
, buffer_(0)
, source_(0)
, wave_() {
	Load(name);
}

/**
 * @brief		�f�X�g���N�^
 */
Sound::~Sound() {
	Release();
}


/**
 * @brief		�o�b�t�@�̃t�H�[�}�b�g����
 */
unsigned long Sound::BufferFormat(){
	if (wave_->Type() == WaveFileType::EX)
	{
		if (wave_->ExHeader().nChannels == 1)
		{
			switch (wave_->ExHeader().wBitsPerSample)
			{
			case 4: return alGetEnumValue("AL_FORMAT_MONO_IMA4");
			case 8: return alGetEnumValue("AL_FORMAT_MONO8");
			case 16: return alGetEnumValue("AL_FORMAT_MONO16");
			}
		}
		else if (wave_->ExHeader().nChannels == 2)
		{
			switch (wave_->ExHeader().wBitsPerSample)
			{
			case 4: return alGetEnumValue("AL_FORMAT_STEREO_IMA4");
			case 8: return alGetEnumValue("AL_FORMAT_STEREO8");
			case 16: return alGetEnumValue("AL_FORMAT_STEREO16");
			}
		}
		else if ((wave_->ExHeader().nChannels == 4) && (wave_->ExHeader().wBitsPerSample == 16))
		{
			return alGetEnumValue("AL_FORMAT_QUAD16");
		}
	}
	else if (wave_->Type() == WaveFileType::EXT)
	{
		if ((wave_->ExHeader().nChannels == 1) &&
			((wave_->ExtensibleHeader().dwChannelMask == SPEAKER_FRONT_CENTER) ||
			(wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)) ||
				(wave_->ExtensibleHeader().dwChannelMask == 0)))
		{
			switch (wave_->ExHeader().wBitsPerSample)
			{
			case 4: return alGetEnumValue("AL_FORMAT_MONO_IMA4");
			case 8: return alGetEnumValue("AL_FORMAT_MONO8");
			case 16: return alGetEnumValue("AL_FORMAT_MONO16");
			}
		}
		else if ((wave_->ExHeader().nChannels == 2) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT)))
		{
			switch (wave_->ExHeader().wBitsPerSample)
			{
			case 4: return alGetEnumValue("AL_FORMAT_STEREO_IMA4");
			case 8: return alGetEnumValue("AL_FORMAT_STEREO8");
			case 16: return alGetEnumValue("AL_FORMAT_STEREO16");
			}
		}
		else if ((wave_->ExHeader().nChannels == 2) && (wave_->ExHeader().wBitsPerSample == 16) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)))
		{
			return alGetEnumValue("AL_FORMAT_REAR16");
		}
		else if ((wave_->ExHeader().nChannels == 4) && (wave_->ExHeader().wBitsPerSample == 16) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)))
		{
			return alGetEnumValue("AL_FORMAT_QUAD16");
		}
		else if ((wave_->ExHeader().nChannels == 6) && (wave_->ExHeader().wBitsPerSample == 16) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT)))
		{
			return alGetEnumValue("AL_FORMAT_51CHN16");
		}
		else if ((wave_->ExHeader().nChannels == 7) && (wave_->ExHeader().wBitsPerSample == 16) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_BACK_CENTER)))
		{
			return alGetEnumValue("AL_FORMAT_61CHN16");
		}
		else if ((wave_->ExHeader().nChannels == 8) && (wave_->ExHeader().wBitsPerSample == 16) && (wave_->ExtensibleHeader().dwChannelMask == (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | SPEAKER_SIDE_LEFT | SPEAKER_SIDE_RIGHT)))
		{
			return alGetEnumValue("AL_FORMAT_71CHN16");
		}
	}
	return 0;
}
/**
 * @brief		�ǂݍ���
 * @param[in]	name	�ǂݍ��ރe�N�X�`����
 * @return		true	�ǂݍ��ݐ���
 *				false	�ǂݍ��ݎ��s
 */
bool Sound::Load(const char* name) {
	//�o�b�t�@�̐���
	alGenBuffers(1, &buffer_);

	//�t�@�C���ǂݍ���
	wave_ = std::make_shared<WaveFile>();
	WaveResult wr = wave_->Load(name);
	if (wr != WaveResult::OK)
	{
		ERROR_LOG("�T�E���h" << name << "���ǂݍ��߂܂���[�G���[�R�[�h:" << static_cast<int>(wr) << "]");
		return false;
	}
	// Set XRAM Mode (if application)
	// if (eaxSetBufferMode && eXRAMBufferMode)
	// 	eaxSetBufferMode(1, &uiBufferID, eXRAMBufferMode);

	alGetError();
	alBufferData(buffer_, BufferFormat(), wave_->Data(), wave_->Size(), wave_->Frequency());
	if (alGetError() != AL_NO_ERROR)
	{
		ERROR_LOG("�T�E���h[" << name << "]�o�b�t�@�̐����Ɏ��s");
		return false;
	}
	//�\�[�X�̐���
	alGenSources(1, &source_);
	//�\�[�X�Ƀo�b�t�@���A�^�b�`
	alSourcei(source_, AL_BUFFER, buffer_);
	name_ = name;
	INFO_LOG("�T�E���h" << name << "��ǂݍ���...");
	return true;
}

/**
 * @brief		�Đ�
 */
void Sound::Play() {
	if (source_ == 0)
	{
		return;
	}
	alSourcePlay(source_);
}

/**
 * @brief		��~
 */
void Sound::Stop() {
	if (source_ == 0)
	{
		return;
	}
	alSourceStop(source_);
}

/**
 * @brief		�������
 */
void Sound::Release() {
	if (buffer_ == 0)
	{
		return;
	}
	alSourceStop(source_);
	alDeleteSources(1, &source_);
	alDeleteBuffers(1, &buffer_);
	wave_.reset();
	INFO_LOG("�T�E���h" << name_ << "�����...");
	name_ = "";
	buffer_ = 0;
	source_ = 0;
}

/**
 * @brief		���[�v�ݒ�
 * @param[in]	p	���[�v�t���O(AL_TRUE�F���[�v����AAL_FALSE:�F���[�v����)
 */
void Sound::Loop(const ALint& p) {
	alSourcei(source_, AL_LOOPING, p);
}