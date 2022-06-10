#pragma once

#include	"../Common/Common.h"

//WAVE�t�H�[�}�b�g����`����Ă��Ȃ����̂��߂̎��O��`
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
	WORD    wFormatTag;
	WORD    nChannels;
	DWORD   nSamplesPerSec;
	DWORD   nAvgBytesPerSec;
	WORD    nBlockAlign;
	WORD    wBitsPerSample;
	WORD    cbSize;
} WAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */

#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct {
	WAVEFORMATEX    Format;
	union {
		WORD wValidBitsPerSample;       /* bits of precision  */
		WORD wSamplesPerBlock;          /* valid if wBitsPerSample==0 */
		WORD wReserved;                 /* If neither applies, set to zero. */
	} Samples;
	DWORD           dwChannelMask;      /* which channels are */
										/* present in stream  */
	GUID            SubFormat;
} WAVEFORMATEXTENSIBLE, * PWAVEFORMATEXTENSIBLE;
#endif // !_WAVEFORMATEXTENSIBLE_

namespace Sample {

	/**
	 * @brief		Wave�t�@�C���̊g���X�^�C�����������߂̃^�C�v��`
	 */
	enum class WaveFileType
	{
		Default = 0,
		EX = 1,
		EXT = 2
	};

	/**
	 * @brief		Wave�t�@�C���̓ǂݍ��݌��ʖ߂�l
	 */
	enum class WaveResult
	{
		OK = 0,
		INVALIDFILENAME = -1,
		BADWAVEFILE = -2,
		INVALIDPARAM = -3,
		INVALIDFILE = -4,
		NOTSUPPORTEDYET = -5,
		WAVEMUSTBEMONO = -6,
		WAVEMUSTBEWAVEFORMATPCM = -7,
		WAVESMUSTHAVESAMEBITRESOLUTION = -8,
		WAVESMUSTHAVESAMEFREQUENCY = -9,
		WAVESMUSTHAVESAMEBITRATE = -10,
		WAVESMUSTHAVESAMEBLOCKALIGNMENT = -11,
		OFFSETOUTOFDATARANGE = -12,
		FILEERROR = -13,
		OUTOFMEMORY = -14,
		INVALIDSPEAKERPOS = -15,
		INVALIDWAVEFILETYPE = -16,
		NOTWAVEFORMATEXTENSIBLEFORMAT = -17
	};

	/**
	 * @brief		WAVE�t�@�C�����������߂̃N���X
	 */
	class WaveFile
	{
	public:
		/**
		 * @brief		WAVE�t�@�C���̓������
		 */
		struct Info
		{
			WaveFileType			wfType;
			WAVEFORMATEXTENSIBLE	wfEXT;
			char*					pData;
			unsigned long			ulDataSize;
			FILE*					pFile;
			unsigned long			ulDataOffset;
		};

	private:
		/** Wave�t�@�C����� */
		Info						info_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		WaveFile();
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~WaveFile();

		/**
		 * @brief		�������
		 */
		void Release();

		/**
		 * @brief		�t�@�C�����J��
		 * @param[in]	name	�ǂݍ���WAVE��
		 * @return		WAVERESULT�Q��
		 */
		WaveResult Open(const char* name);

		/**
		 * @brief		�ǂݍ���
		 * @param[in]	name	�ǂݍ���WAVE��
		 * @return		WAVERESULT�Q��
		 */
		WaveResult Load(const char* name);

		/**
		 * @brief		�ǂݍ���
		 * @param[in/out]	size	�ǂݍ��ރo�b�t�@
		 * @param[in]		size	�ǂݍ��ރT�C�Y
		 * @param[in/out]	outSize	�ǂݍ��񂾃T�C�Y
		 * @return		WAVERESULT�Q��
		 */
		WaveResult Read(void* pData, unsigned long size, unsigned long* outSize);

		/**
		 * @brief		�ǂݍ��݈ʒu�ύX
		 * @param[in]	Offset	�ʒu
		 * @return		WAVERESULT�Q��
		 */
		WaveResult Seek(unsigned long Offset);

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const WaveFileType Type() const noexcept { return info_.wfType; }
		const WAVEFORMATEX& ExHeader() const noexcept { return info_.wfEXT.Format; }
		const WAVEFORMATEXTENSIBLE& ExtensibleHeader() const noexcept { return info_.wfEXT; }
		const char* Data() const noexcept { return info_.pData; }
		const unsigned long Size() const noexcept { return info_.ulDataSize; }
		const unsigned long Offset() const noexcept {
			if (!info_.pFile)
			{
				return 0;
			}
			return ftell(info_.pFile) - info_.ulDataOffset;
		}
		const unsigned long Frequency() const noexcept { return info_.wfEXT.Format.nSamplesPerSec; }
	};
	using WaveFilePtr = std::shared_ptr< WaveFile >;

}