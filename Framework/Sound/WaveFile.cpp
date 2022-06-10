#include	"WaveFile.h"

using namespace Sample;

#pragma pack(push, 4)

struct WaveFileHeader
{
	char			szRIFF[4];
	unsigned long	ulRIFFSize;
	char			szWAVE[4];
};

struct RiffChunk
{
	char			szChunkName[4];
	unsigned long	ulChunkSize;
};

struct WaveFormat
{
	unsigned short	usFormatTag;
	unsigned short	usChannels;
	unsigned long	ulSamplesPerSec;
	unsigned long	ulAvgBytesPerSec;
	unsigned short	usBlockAlign;
	unsigned short	usBitsPerSample;
	unsigned short	usSize;
	unsigned short  usReserved;
	unsigned long	ulChannelMask;
    GUID            guidSubFormat;
};

#pragma pack(pop)

/**
 * @brief		�R���X�g���N�^
 */
WaveFile::WaveFile() {
	memset(&info_, 0, sizeof(info_));
}

/**
 * @brief		�f�X�g���N�^
 */
WaveFile::~WaveFile()
{
}


/**
 * @brief		�������
 */
void WaveFile::Release() {
	SAFE_DELETE(info_.pData);
	if (info_.pFile)
	{
		fclose(info_.pFile);
		info_.pFile = nullptr;
	}
}

/**
 * @brief		�t�@�C�����J��
 * @param[in]	name	�ǂݍ���WAVE��
 * @return		WAVERESULT�Q��
 */
WaveResult WaveFile::Open(const char* name) {
	WaveFileHeader	waveFileHeader;
	RiffChunk		riffChunk;
	WaveFormat		waveFmt;
	if (!name)
	{
		return WaveResult::INVALIDPARAM;
	}
	memset(&info_, 0, sizeof(info_));
	fopen_s(&info_.pFile, name, "rb");
	if (info_.pFile == nullptr)
	{
		return WaveResult::INVALIDFILENAME;
	}
	//�w�b�_�[�ǂݍ���
	fread(&waveFileHeader, 1, sizeof(WaveFileHeader), info_.pFile);
	if (!_strnicmp(waveFileHeader.szRIFF, "RIFF", 4) && !_strnicmp(waveFileHeader.szWAVE, "WAVE", 4))
	{
		while (fread(&riffChunk, 1, sizeof(RiffChunk), info_.pFile) == sizeof(RiffChunk))
		{
			if (!_strnicmp(riffChunk.szChunkName, "fmt ", 4))
			{
				if (riffChunk.ulChunkSize <= sizeof(WaveFormat))
				{
					fread(&waveFmt, 1, riffChunk.ulChunkSize, info_.pFile);
					if (waveFmt.usFormatTag == WAVE_FORMAT_PCM)
					{
						info_.wfType = WaveFileType::EX;
						memcpy(&info_.wfEXT.Format, &waveFmt, sizeof(PCMWAVEFORMAT));
					}
					else if (waveFmt.usFormatTag == WAVE_FORMAT_EXTENSIBLE)
					{
						info_.wfType = WaveFileType::EXT;
						memcpy(&info_.wfEXT, &waveFmt, sizeof(WAVEFORMATEXTENSIBLE));
					}
				}
				else
				{
					fseek(info_.pFile, riffChunk.ulChunkSize, SEEK_CUR);
				}
			}
			else if (!_strnicmp(riffChunk.szChunkName, "data", 4))
			{
				info_.ulDataSize = riffChunk.ulChunkSize;
				info_.ulDataOffset = ftell(info_.pFile);
				fseek(info_.pFile, riffChunk.ulChunkSize, SEEK_CUR);
			}
			else
			{
				fseek(info_.pFile, riffChunk.ulChunkSize, SEEK_CUR);
			}
			if (riffChunk.ulChunkSize & 1)
			{
				fseek(info_.pFile, 1, SEEK_CUR);
			}
		}

		if (info_.ulDataSize && info_.ulDataOffset && ((info_.wfType == WaveFileType::EX) || (info_.wfType == WaveFileType::EXT)))
		{
			return WaveResult::OK;
		}
		else
		{
			fclose(info_.pFile);
		}
	}
	return WaveResult::BADWAVEFILE;
}

/**
 * @brief		�ǂݍ���
 * @param[in]	name	�ǂݍ���WAVE��
 * @return		WAVERESULT�Q��
 */
WaveResult WaveFile::Load(const char* name) {
	WaveResult wr = Open(name);
	if (wr != WaveResult::OK)
	{
		return wr;
	}
	//�������m��
	info_.pData = new char[info_.ulDataSize];
	if (!info_.pData)
	{
		return WaveResult::OUTOFMEMORY;
	}
	fseek(info_.pFile, info_.ulDataOffset, SEEK_SET);
	if (fread(info_.pData, 1, info_.ulDataSize, info_.pFile) != info_.ulDataSize)
	{
		SAFE_DELETE(info_.pData);
		fclose(info_.pFile);
		info_.pFile = nullptr;
		return WaveResult::BADWAVEFILE;
	}
	fclose(info_.pFile);
	info_.pFile = nullptr;
	return WaveResult::OK;
}

/**
 * @brief		�ǂݍ���
 * @param[in/out]	size	�ǂݍ��ރo�b�t�@
 * @param[in]		size	�ǂݍ��ރT�C�Y
 * @param[in/out]	outSize	�ǂݍ��񂾃T�C�Y
 * @return		WAVERESULT�Q��
 */
WaveResult WaveFile::Read(void* pData, unsigned long size, unsigned long* outSize){
	if (!pData || !outSize || size == 0)
	{
		return WaveResult::INVALIDPARAM;
	}
	if (!info_.pFile)
	{
		return WaveResult::INVALIDFILE;
	}
	unsigned long ulOffset = ftell(info_.pFile);
	if ((ulOffset - info_.ulDataOffset + size) > info_.ulDataSize)
	{
		size = info_.ulDataSize - (ulOffset - info_.ulDataOffset);
	}
	*outSize = (unsigned long)fread(pData, 1, size, info_.pFile);
	return WaveResult::OK;
}

/**
 * @brief		�ǂݍ��݈ʒu�ύX
 * @param[in]	Offset	�ʒu
 * @return		WAVERESULT�Q��
 */
WaveResult WaveFile::Seek(unsigned long Offset) {
	if (!info_.pFile)
	{
		return WaveResult::INVALIDFILE;
	}
	fseek(info_.pFile, info_.ulDataOffset + Offset, SEEK_SET);
	return WaveResult::OK;
}