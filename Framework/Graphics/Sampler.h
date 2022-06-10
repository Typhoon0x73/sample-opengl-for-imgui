#pragma once

#include	"../Resource/ResourceBase.h"

namespace Sample {

	/**
	 * @brief		�e�N�X�`���T���v�����������߂̃N���X
	 */
	class Sampler
	{
	public:
		enum class Wrap {
			Clamp,
			Repeat,
			Mirror,
		};

		enum class Filter {
			Nearest,
			Linear,
		};

	protected:
		/** �T���v��ID */
		GLuint			id_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Sampler()
			: id_(0) {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Sampler() {
			Release();
		}

		/**
		 * @brief		����
		 * @return		true	����
		 *				false	���s
		 */
		bool Create() {
			glCreateSamplers(1, &id_);
			GL_ERROR_RETURN("�T���v���̐����Ɏ��s...", false);
			return true;
		}

		/**
		 * @brief		���b�v���[�h�̐ݒ�
		 * @param[in]	mode	���[�h
		 * @return		true	����
		 *				false	���s
		 */
		bool WrapMode(Wrap mode) {
			switch (mode)
			{
			case Wrap::Clamp:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;

			case Wrap::Repeat:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;

			case Wrap::Mirror:
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			}
			GL_ERROR_RETURN("���b�v���[�h�̐ݒ�Ɏ��s...", false);
			return true;
		}

		/**
		 * @brief		�t�B���^�[���[�h�̐ݒ�
		 * @param[in]	min		�k�����[�h
		 * @param[in]	mag		�g�僂�[�h
		 * @return		true	����
		 *				false	���s
		 */
		bool FilterMode(Filter min, Filter mag) {
			switch (min)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("�t�B���^�̐ݒ�Ɏ��s...", false);

			switch (mag)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("�t�B���^�̐ݒ�Ɏ��s...", false);
			return true;
		}

		/**
		 * @brief		�t�B���^�[���[�h�̐ݒ�
		 * @param[in]	min		�k�����[�h
		 * @param[in]	mag		�g�僂�[�h
		 * @param[in]	mip		�~�b�v�}�b�v���[�h
		 * @return		true	����
		 *				false	���s
		 */
		bool FilterMode(Filter min, Filter mag, Filter mip) {
			switch (min)
			{
			case Filter::Nearest:
				switch (mip)
				{
				case Filter::Nearest:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
					break;

				case Filter::Linear:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
					break;
				}
				break;

			case Filter::Linear:
				switch (mip)
				{
				case Filter::Nearest:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
					break;

				case Filter::Linear:
					glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					break;
				}
				break;
			}
			GL_ERROR_RETURN("�t�B���^�̐ݒ�Ɏ��s...", false);

			switch (mag)
			{
			case Filter::Nearest:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			case Filter::Linear:
				glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}
			GL_ERROR_RETURN("�t�B���^�̐ݒ�Ɏ��s...", false);
			return true;
		}

		/**
		 * @brief		�������
		 */
		void Release() {
			if (id_ == 0)
			{
				return;
			}
			glDeleteSamplers(1, &id_);
			id_ = 0;
		}

		/**
		 * @brief		�e��擾�݂̂̃��\�b�h
		 */
		const GLuint ID() const noexcept { return id_; }

	};
	using SamplerPtr = std::shared_ptr< Sampler >;

}