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

	class PolyLine {
	public:
		/** ���C����� */
		struct Line {
			Vector3F		pos;
			Vector3F		front;
			float			width;
			Vector4F		color;
		};
		using LineArray = std::vector<Line>;

	protected:
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

		/** �`��p���_��� */
		struct Vertex {
			glm::vec3		pos;
			glm::vec2		uv;
			glm::vec4		color;
		};
		/** �`�撸�_�z�� */
		std::vector<Vertex>	vertices;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		PolyLine()
		: texture_()
		, sampler_()
		, shader_()
		, vertexBuffer_()
		, indexBuffer_() 
		, vertexArrayID(0)
		, vertices() {
		}
		/**
		 * @brief		�R���X�g���N�^
		 */
		PolyLine(const PolyLine& obj)
		: texture_(obj.texture_)
		, sampler_(obj.sampler_)
		, shader_(obj.shader_)
		, vertexBuffer_()
		, indexBuffer_() 
		, vertexArrayID(0) 
		, vertices() {
			Create(obj.texture_, obj.shader_);
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~PolyLine() {
			Release();
		}

		/**
		 * @brief		��������
		 * @param[in]	t	�g���e�N�X�`��
		 * @param[in]	s	�g���V�F�[�_�[
		 */
		void Create(const TexturePtr t, const ShaderPtr s, const GLuint lineCount = 100) {
			//�e�N�X�`���ݒ�
			texture_ = t;
			//�V�F�[�_�[�o�^
			shader_ = s;

			//�T�C�Y
			GLuint size = (lineCount - 1) * 4;
			//�|���S���p�̃f�[�^����
			vertices.resize(size);
			vertexBuffer_.Create(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), vertices.data(), GL_STREAM_DRAW);
			vertices.clear();

			std::vector<GLuint> idx;
			idx.resize(size);
			for (GLuint i = 0; i < size; i++)
			{
				idx[i] = i;
			}
			indexBuffer_.Create(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

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
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(20));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/**
		 * @brief		���_���̍X�V
		 */
		void RefreshVertex(const LineArray& lines) {
			//���܂ł̃f�[�^�폜
			vertices.clear();

			//���C���̐��s��
			if (lines.size() <= 1)
			{
				return;
			}

			Vertex out[2];
			Vector3F fvec = GraphicsController::GetInstance().Camera()->Forward();
			float av = 1.0f / (lines.size() - 1);
			float v = 0;
			for (const auto& line : lines)
			{
				Vector3F cv = Vector3F::Cross(fvec, line.front);
				Vector3F lpos = line.pos - cv * line.width;
				Vector3F rpos = line.pos + cv * line.width;
				out[0].pos = glm::vec3(lpos.x, -lpos.y, lpos.z);
				out[0].uv = glm::vec2(0, v);
				out[0].color = glm::vec4(line.color.r, line.color.g, line.color.b, line.color.a);

				out[1].pos = glm::vec3(rpos.x, -rpos.y, rpos.z);
				out[1].uv = glm::vec2(1, v);
				out[1].color = glm::vec4(line.color.r, line.color.g, line.color.b, line.color.a);

				vertices.insert(vertices.end(), out, out + 2);
				v += av;
			}

			vertexBuffer_.SubData(0, sizeof(Vertex) * vertices.size(), vertices.data());
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
			std::for_each(binder.begin(), binder.end(), [](const ShaderParameterBindPtr& ptr) { ptr->Bind(); });

			if (sampler_)
			{
				shader_->BindSampler(0, sampler_->ID());
			}
			shader_->BindTexture(0, texture_->ID());
			glDrawElements(GL_TRIANGLE_STRIP, vertices.size(), GL_UNSIGNED_INT, 0);
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
	using PolyLinePtr = std::shared_ptr< PolyLine >;
}