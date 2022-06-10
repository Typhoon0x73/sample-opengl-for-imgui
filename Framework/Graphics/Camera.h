#pragma once

#include	"../Math/Vector3.h"

namespace Sample {

	class Camera
	{
	private:
		/** �J�����̈ʒu */
		Vector3F			position_;
		/** �J�����̑O�� */
		Vector3F			forward_;

		/** �r���[�v���W�F�N�V�����s�� */
		glm::mat4			matVP_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Camera()
			: position_()
		, forward_()
			, matVP_() {
		}
		/**
		 * @brief		�R�s�[�R���X�g���N�^
		 * @param[in]	obj	�R�s�[����J����
		 */
		Camera(const Camera& obj)
			: position_(obj.position_)
		, forward_(obj.forward_)
			, matVP_(obj.matVP_) {
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~Camera() {
		}

		/**
		 * @brief		2D�p�J�����̐���
		 * @param[in]	w	��
		 * @param[in]	h	����
		 */
		void Create2D(int w, int h) {
			forward_ = Vector3F(0, 0, -1);
			const glm::vec2 hs(w * 0.5f, h * 0.5f);
			const glm::mat4x4 matProj = glm::ortho(-hs.x, hs.x, -hs.y, hs.y, 1.0f, 1000.0f);
			const glm::mat4x4 matView = glm::lookAt(
				glm::vec3(hs.x + position_.x, -hs.y - position_.y, 100),
				glm::vec3(hs.x + position_.x, -hs.y - position_.y, 0), glm::vec3(0, 1, 0));
			matVP_ = matProj * matView;
		}

		/**
		 * @brief		Position�ւ�Accessor
		 * @param[in]	p	�ʒu
		 */
		void Position(const Vector3F& p) { position_ = p; }
		/**
		 * @brief		Position�ւ�Accessor
		 * @return		�ʒu
		 */
		const Vector3F& Position() const noexcept { return position_; }

		/**
		 * @brief		Forward�ւ�Accessor
		 * @return		�O������
		 */
		const Vector3F& Forward() const noexcept { return forward_; }

		/**
		 * @brief		matVP_�ւ�Accessor
		 * @return		�r���[�v���W�F�N�V����
		 */
		const glm::mat4& ViewProjection() const { return matVP_; }
	};
	//�|�C���^�u������
	using CameraPtr = std::shared_ptr<Camera>;

}