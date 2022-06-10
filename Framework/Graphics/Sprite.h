#pragma once

#include	"../Math/Rectangle.h"
#include	"../Math/Vector4.h"
#include	"Texture.h"
#include	"Sampler.h"
#include	"Buffer.h"
#include	"Shader.h"
#include	"ShaderParameterBind.h"
#include	"GraphicsController.h"

namespace Sample {

	class Sprite {
	protected:
		/** �X�v���C�g�̈ʒu */
		Vector3F	position_;
		/** �X�v���C�g�̌��� */
		Vector3F	rotation_;
		/** �X�v���C�g�̑傫�� */
		Vector3F	scale_;

		/** �X�v���C�g�̕`��s�� */
		glm::mat4	matModel_;

		/** �A���J�[ */
		Vector3F	anchor_;
		/** �s�{�b�g */
		Vector3F	pivot_;
		/** �e���_�ւ̕␳�l */
		Vector3F	offset_[4];

		/** �F */
		Vector4F	color_;

		/** ���݂̃A�j���[�V������` */
		RectangleF	srcRect_;

		/** �����]�t���O */
		bool		xflip_;
		/** �c���]�t���O */
		bool		yflip_;

		/** ���p����e�N�X�`�� */
		TexturePtr	texture_;
		/** ���p����T���v�� */
		SamplerPtr	sampler_;
		/** ���p����摜 */
		ShaderPtr	shader_;

		/** �`��p�o�b�t�@ */
		Buffer		vertexBuffer_;
		/** �`��p�o�b�t�@ */
		Buffer		indexBuffer_;

		/** ���_�z�� */
		GLuint		vertexArrayID;
		/** ���_�J���[ */
		GLuint		colorLocation;

		/** �`��p���_��� */
		struct Vertex {
			float pos[3];
			float uv[2];
		};

		/**
		 * @brief			���_�������߂�
		 * @param[in/out]	out	�o�͂��钸�_���
		 */
		void GetVertex(Vertex* out) {
			//�|���S���f�[�^�쐬
			float tw = (float)texture_->Width();
			float th = (float)texture_->Height();
			//UV
			float lt = srcRect_.Left / tw;
			float rt = srcRect_.Right / tw;
			float ut = srcRect_.Top / th;
			float bt = srcRect_.Bottom / th;
			if (xflip_)
			{
				float tmp = rt;
				rt = lt;
				lt = tmp;
			}
			if (yflip_)
			{
				float tmp = bt;
				bt = ut;
				ut = tmp;
			}
			//�ʒu
			float lx = pivot_.x * -srcRect_.Width();
			float rx = (1 - pivot_.x) * srcRect_.Width();
			float uy = pivot_.y * srcRect_.Height();
			float by = (1 - pivot_.y) * -srcRect_.Height();
			//���_���
			out[0].pos[0] = lx + offset_[0].x;	out[0].pos[1] = by - offset_[0].y;	out[0].pos[2] = 0 + offset_[0].z;	out[0].uv[0] = lt;	out[0].uv[1] = bt;
			out[1].pos[0] = rx + offset_[1].x;	out[1].pos[1] = by - offset_[1].y;	out[1].pos[2] = 0 + offset_[1].z;	out[1].uv[0] = rt;	out[1].uv[1] = bt;
			out[2].pos[0] = lx + offset_[2].x;	out[2].pos[1] = uy - offset_[2].y;	out[2].pos[2] = 0 + offset_[2].z;	out[2].uv[0] = lt;	out[2].uv[1] = ut;
			out[3].pos[0] = rx + offset_[3].x;	out[3].pos[1] = uy - offset_[3].y;	out[3].pos[2] = 0 + offset_[3].z;	out[3].uv[0] = rt;	out[3].uv[1] = ut;
		}

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Sprite()
		: position_()
		, rotation_()
		, scale_(1,1,1)
		, matModel_()
		, anchor_()
		, pivot_()
		, color_(1, 1, 1, 1)
		, srcRect_(0, 0, 0, 0)
		, xflip_(false)
		, yflip_(false)
		, texture_()
		, sampler_()
		, shader_()
		, vertexBuffer_()
		, indexBuffer_() 
		, vertexArrayID(0) 
		, colorLocation(0) {
		}
		/**
		 * @brief		�R���X�g���N�^
		 */
		Sprite(const Sprite& obj)
		: position_(obj.position_)
		, rotation_(obj.rotation_)
		, scale_(obj.scale_)
		, matModel_(obj.matModel_)
		, anchor_(obj.anchor_)
		, pivot_(obj.pivot_)
		, color_(obj.color_)
		, srcRect_(obj.srcRect_)
		, xflip_(obj.xflip_)
		, yflip_(obj.yflip_)
		, texture_(obj.texture_)
		, sampler_(obj.sampler_)
		, shader_(obj.shader_)
		, vertexBuffer_()
		, indexBuffer_() 
		, vertexArrayID(0) 
		, colorLocation(0) {
			Create(obj.texture_, obj.shader_);
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~Sprite() {
			Release();
		}

		/**
		 * @brief		��������
		 * @param[in]	t	�g���e�N�X�`��
		 * @param[in]	s	�g���V�F�[�_�[
		 */
		void Create(const TexturePtr t, const ShaderPtr s) {
			if (texture_ != t)
			{
				//�f�ސݒ�
				texture_ = t;
				//��`�ݒ�
				srcRect_.Left = 0;
				srcRect_.Right = static_cast<float>(texture_->Width());
				srcRect_.Top = 0;
				srcRect_.Bottom = static_cast<float>(texture_->Height());
			}
			shader_ = s;
			//���_�f�[�^�����߂�
			Vertex vx[4];
			GetVertex(vx);
			//�|���S���f�[�^�쐬
			GLushort idx[4] = { 0,1,2,3 };
			vertexBuffer_.Create(GL_ARRAY_BUFFER, sizeof(vx), vx, GL_STREAM_DRAW);
			indexBuffer_.Create(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

			//���_�f�[�^�z��쐬
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_.ID());
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(12));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			colorLocation = shader_->GetUniformLocation("baseColor");
		}

		/**
		 * @brief		���_���̍X�V
		 */
		void RefreshVertex() {
			Vertex vx[4];
			GetVertex(vx);
			vertexBuffer_.SubData(0, sizeof(vx), vx);
		}

		/**
		 * @brief		�s��̍X�V
		 */
		void RefreshMatrix() {
			float tx = GraphicsController::GetInstance().ScreenWidth() * anchor_.x;
			float ty = GraphicsController::GetInstance().ScreenHeight() * anchor_.y;
			const glm::mat4 matT = glm::translate(glm::mat4(1), glm::vec3(tx + position_.x, -ty + -position_.y, position_.z));
			const glm::mat4 matRY = glm::rotate(matT, glm::radians(rotation_.y), glm::vec3(0, 1, 0));
			const glm::mat4 matRXY = glm::rotate(matRY, glm::radians(rotation_.x), glm::vec3(1, 0, 0));
			const glm::mat4 matRZXY = glm::rotate(matRXY, glm::radians(-rotation_.z), glm::vec3(0, 0, 1));
			const glm::mat4 matS = glm::scale(matRZXY, glm::vec3(scale_.x, scale_.y, scale_.z));
			matModel_ = matS;
		}

		/**
		 * @brief		�X�v���C�g��\��������
		 */
		void Render(const ShaderParameterBindList& binder = {}) {
			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());
			shader_->Enable();

			auto mvp = GraphicsController::GetInstance().Camera()->ViewProjection();
			shader_->SetViewProjectionMatrix(&mvp[0][0]);
			shader_->SetModelMatrix(&matModel_[0][0]);
			glUniform4fv(colorLocation, 1, &color_[0]);
			std::for_each(binder.begin(), binder.end(), [](const ShaderParameterBindPtr& ptr) { ptr->Bind(); });

			if (sampler_)
			{
				shader_->BindSampler(0, sampler_->ID());
			}
			shader_->BindTexture(0, texture_->ID());
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
			shader_->BindTexture(0, 0);
			shader_->BindSampler(0, 0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/**
		 * @brief		�������
		 */
		void Release() {
			if (vertexArrayID > 0)
			{
				glDeleteVertexArrays(1, &vertexArrayID);
				vertexArrayID = 0;
			}
		}

		/**
		 * @brief		pos�ւ�Accessor
		 * @param[in]	p	�ʒu
		 */
		void Position(const Vector3F& p) { position_ = p; }
		/**
		 * @brief		pos�ւ�Accessor
		 * @return		�ʒu
		 */
		const Vector3F& Position() const noexcept { return position_; }

		/**
		 * @brief		rotation�ւ�Accessor
		 * @param[in]	p	����
		 */
		void Rotation(const Vector3F& p) { rotation_ = p; }
		/**
		 * @brief		rotation�ւ�Accessor
		 * @return		����
		 */
		const Vector3F& Rotation() const noexcept { return rotation_; }

		/**
		 * @brief		scale�ւ�Accessor
		 * @param[in]	p	�傫��
		 */
		void Scale(const Vector3F& p) { scale_ = p; }
		/**
		 * @brief		scale�ւ�Accessor
		 * @return		�傫��
		 */
		const Vector3F& Scale() const noexcept { return scale_; }

		/**
		 * @brief		pivot�ւ�Accessor
		 * @param[in]	p	�s�{�b�g
		 */
		void Pivot(const Vector3F& p) { pivot_ = p; }
		/**
		 * @brief		pivot�ւ�Accessor
		 * @return		�s�{�b�g
		 */
		const Vector3F& Pivot() const noexcept { return pivot_; }

		/**
		 * @brief		anchor�ւ�Accessor
		 * @param[in]	p	�A���J�[
		 */
		void Anchor(const Vector3F& p) { anchor_ = p; }
		/**
		 * @brief		anchor�ւ�Accessor
		 * @return		�A���J�[
		 */
		const Vector3F& Anchor() const noexcept { return anchor_; }

		/**
		 * @brief		��`�擾
		 * @return		��`
		 */
		const RectangleF& SrcRect() const {
			return srcRect_;
		}

		/**
		 * @brief		��`�ݒ�
		 * @param[in]	��`
		 */
		const void SrcRect(const RectangleF& r) {
			if (srcRect_ != r)
			{
				srcRect_ = r;
				RefreshVertex();
			}
		}

		/**
		 * @brief		color_�ւ�Accessor
		 * @param[in]	�A���t�@�l
		 */
		void Alpha(const float a) {
			color_.a = a;
		}

		/**
		 * @brief		color_�ւ�Accessor
		 * @return		�A���t�@�l
		 */
		const float Alpha(void) const {
			return color_.a;
		}

		/**
		 * @brief		color_�ւ�Accessor
		 * @param[in]	c	�F
		 */
		void Color(const Vector4F& c) { color_ = c; }
		/**
		 * @brief		color_�ւ�Accessor
		 * @return		�F
		 */
		const Vector4F& Color() const noexcept { return color_; }

		/**
		 * @brief		xflip_�ւ�Accessor
		 * @param[in]	f	���]�t���O
		 */
		void XFlip(bool f)
		{
			xflip_ = f;
		}
		/**
		 * @brief		xflip_�ւ�Accessor
		 * @return		���]�t���O
		 */
		const bool XFlip() const noexcept { return xflip_; }

		/**
		 * @brief		yflip_�ւ�Accessor
		 * @param[in]	f	���]�t���O
		 */
		void YFlip(bool f)
		{
			yflip_ = f;
		}
		/**
		 * @brief		yflip_�ւ�Accessor
		 * @return		���]�t���O
		 */
		const bool YFlip() const noexcept { return yflip_; }

		/**
		 * @brief		���_�I�t�Z�b�g�ւ�Accessor
		 * @param[in]	n	�I�t�Z�b�g�ԍ�
		 * @param[in]	p	�I�t�Z�b�g�ʒu
		 */
		void VertexOffset(const int n, const Vector3F& p) { offset_[n] = p; }
		/**
		 * @brief		���_�I�t�Z�b�g�ւ�Accessor
		 * @return		���_�I�t�Z�b�g
		 */
		const Vector3F* VertexOffset() const noexcept { return offset_; }

		/**
		 * @brief		Texture_�ւ�Accessor
		 * @return		�e�N�X�`��
		 */
		const TexturePtr Texture(void) const {
			return texture_;
		}

		/**
		 * @brief		Sampler_�ւ�Accessor
		 * @return		�T���v��
		 */
		void Sampler(const SamplerPtr& v) noexcept { sampler_ = v; }
		/**
		 * @brief		Sampler_�ւ�Accessor
		 * @return		�T���v��
		 */
		const SamplerPtr Sampler(void) const {
			return sampler_;
		}

		/**
		 * @brief		Shader�ւ�Accessor
		 * @return		�V�F�[�_�[
		 */
		const ShaderPtr Shader(void) const {
			return shader_;
		}

	};
	using SpritePtr = std::shared_ptr< Sprite >;
}