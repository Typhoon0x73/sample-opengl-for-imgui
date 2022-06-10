#include	"Sound.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
Sound::Sound()
: ResourceBase()
, buffer_(0)
, source_(0)
, wave_() {
}

/**
 * @brief		コンストラクタ
 *				生成と同時に読み込みをおこなう
 * @param[in]	name	読み込むテクスチャ名
 */
Sound::Sound(const char* name)
: ResourceBase()
, buffer_(0)
, source_(0)
, wave_() {
	Load(name);
}

/**
 * @brief		デストラクタ
 */
Sound::~Sound() {
	Release();
}


/**
 * @brief		バッファのフォーマット判定
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
 * @brief		読み込み
 * @param[in]	name	読み込むテクスチャ名
 * @return		true	読み込み成功
 *				false	読み込み失敗
 */
bool Sound::Load(const char* name) {
	//バッファの生成
	alGenBuffers(1, &buffer_);

	//ファイル読み込み
	wave_ = std::make_shared<WaveFile>();
	WaveResult wr = wave_->Load(name);
	if (wr != WaveResult::OK)
	{
		ERROR_LOG("サウンド" << name << "が読み込めません[エラーコード:" << static_cast<int>(wr) << "]");
		return false;
	}
	// Set XRAM Mode (if application)
	// if (eaxSetBufferMode && eXRAMBufferMode)
	// 	eaxSetBufferMode(1, &uiBufferID, eXRAMBufferMode);

	alGetError();
	alBufferData(buffer_, BufferFormat(), wave_->Data(), wave_->Size(), wave_->Frequency());
	if (alGetError() != AL_NO_ERROR)
	{
		ERROR_LOG("サウンド[" << name << "]バッファの生成に失敗");
		return false;
	}
	//ソースの生成
	alGenSources(1, &source_);
	//ソースにバッファをアタッチ
	alSourcei(source_, AL_BUFFER, buffer_);
	name_ = name;
	INFO_LOG("サウンド" << name << "を読み込み...");
	return true;
}

/**
 * @brief		再生
 */
void Sound::Play() {
	if (source_ == 0)
	{
		return;
	}
	alSourcePlay(source_);
}

/**
 * @brief		停止
 */
void Sound::Stop() {
	if (source_ == 0)
	{
		return;
	}
	alSourceStop(source_);
}

/**
 * @brief		解放処理
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
	INFO_LOG("サウンド" << name_ << "を解放...");
	name_ = "";
	buffer_ = 0;
	source_ = 0;
}

/**
 * @brief		ループ設定
 * @param[in]	p	ループフラグ(AL_TRUE：ループあり、AL_FALSE:：ループ無し)
 */
void Sound::Loop(const ALint& p) {
	alSourcei(source_, AL_LOOPING, p);
}