#pragma once

#include	"../Resource/ResourceBase.h"
#include	"WaveFile.h"

namespace Sample {

	/**
	 * @brief		���t�@�C�����������߂̃N���X
	 */
	class Sound : public ResourceBase
	{
	protected:
		/** �o�b�t�@ */
		ALuint			buffer_;
		/** �\�[�X */
		ALuint			source_;
		/** Wave�t�@�C�� */
		WaveFilePtr		wave_;

		/**
		 * @brief		�o�b�t�@�̃t�H�[�}�b�g����
		 */
		unsigned long BufferFormat();
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Sound();

		/**
		 * @brief		�R���X�g���N�^
		 *				�����Ɠ����ɓǂݍ��݂������Ȃ�
		 * @param[in]	name	�ǂݍ��ރT�E���h��
		 */
		Sound(const char* name);

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Sound();

		/**
		 * @brief		�ǂݍ���
		 * @param[in]	name	�ǂݍ��ރT�E���h��
		 * @return		true	�ǂݍ��ݐ���
		 *				false	�ǂݍ��ݎ��s
		 */
		bool Load(const char* name);

		/**
		 * @brief		�Đ�
		 */
		void Play();

		/**
		 * @brief		��~
		 */
		void Stop();

		/**
		 * @brief		�������
		 */
		void Release();

		/**
		 * @brief		���[�v�ݒ�
		 * @param[in]	p	���[�v�t���O(AL_TRUE�F���[�v����AAL_FALSE:�F���[�v����)
		 */
		void Loop(const ALint& p);

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const ALuint Buffer() const { return buffer_; }
		const ALuint Source() const { return source_; }
	};
	using SoundPtr = std::shared_ptr< Sound >;
	using SoundArray = std::vector< SoundPtr >;

}