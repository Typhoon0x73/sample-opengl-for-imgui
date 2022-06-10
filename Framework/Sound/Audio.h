#pragma once

#include	"IAudio.h"

namespace Sample {

	class Audio : public IAudio
	{
	private:
		/** AL�f�o�C�X */
		ALCdevice*					alDevice_;
		/** AL�R���e�L�X�g */
		ALCcontext*					alContext_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Audio()
			: alDevice_(nullptr)
			, alContext_(nullptr) {
		}
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Audio() {
			Release();
		}

		/**
		 * @brief		OpenAL�̏�����
		 * @return		true	��������
		 *				false	�������s
		 */
		bool Initialize() override;

		/**
		 * @brief		�������
		 */
		void Release() override;

		/**
		 * @brief		�������f���ݒ�
		 */
		void DistanceModel(ALenum en);
		/**
		 * @brief		�h�b�v���[�ݒ�
		 */
		void DopplerFactor(ALfloat v);
		/**
		 * @brief		�h�b�v���[���x�ݒ�
		 */
		void DopplerVelocity(ALfloat v);

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		ALCdevice* Device() { return alDevice_; }
		ALCcontext* Ccontext() { return alContext_; }
	};
}