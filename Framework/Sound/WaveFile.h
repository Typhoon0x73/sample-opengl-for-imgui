#pragma once

#include	"../Common/Common.h"

//WAVEフォーマットが定義されていない時のための自前定義
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
	 * @brief		Waveファイルの拡張スタイルを扱うためのタイプ定義
	 */
	enum class WaveFileType
	{
		Default = 0,
		EX = 1,
		EXT = 2
	};

	/**
	 * @brief		Waveファイルの読み込み結果戻り値
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
	 * @brief		WAVEファイルを扱うためのクラス
	 */
	class WaveFile
	{
	public:
		/**
		 * @brief		WAVEファイルの内部情報
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
		/** Waveファイル情報 */
		Info						info_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		WaveFile();
		/**
		 * @brief		デストラクタ
		 */
		virtual ~WaveFile();

		/**
		 * @brief		解放処理
		 */
		void Release();

		/**
		 * @brief		ファイルを開く
		 * @param[in]	name	読み込むWAVE名
		 * @return		WAVERESULT参照
		 */
		WaveResult Open(const char* name);

		/**
		 * @brief		読み込み
		 * @param[in]	name	読み込むWAVE名
		 * @return		WAVERESULT参照
		 */
		WaveResult Load(const char* name);

		/**
		 * @brief		読み込み
		 * @param[in/out]	size	読み込むバッファ
		 * @param[in]		size	読み込むサイズ
		 * @param[in/out]	outSize	読み込んだサイズ
		 * @return		WAVERESULT参照
		 */
		WaveResult Read(void* pData, unsigned long size, unsigned long* outSize);

		/**
		 * @brief		読み込み位置変更
		 * @param[in]	Offset	位置
		 * @return		WAVERESULT参照
		 */
		WaveResult Seek(unsigned long Offset);

		/**
		 * @brief		各種取得のみのメソッド
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