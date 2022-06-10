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
		/** ライン情報 */
		struct Line {
			Vector3F		pos;
			Vector3F		front;
			float			width;
			Vector4F		color;
		};
		using LineArray = std::vector<Line>;

	protected:
		/** 利用するテクスチャ */
		TexturePtr	texture_;
		/** 利用するサンプラ */
		SamplerPtr	sampler_;
		/** 利用する画像 */
		ShaderPtr	shader_;

		/** 描画用バッファ */
		Buffer		vertexBuffer_;
		/** 描画用バッファ */
		Buffer		indexBuffer_;

		/** 頂点配列 */
		GLuint		vertexArrayID;

		/** 描画用頂点情報 */
		struct Vertex {
			glm::vec3		pos;
			glm::vec2		uv;
			glm::vec4		color;
		};
		/** 描画頂点配列 */
		std::vector<Vertex>	vertices;

	public:
		/**
		 * @brief		コンストラクタ
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
		 * @brief		コンストラクタ
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
		 * @brief		デストラクタ
		 */
		~PolyLine() {
			Release();
		}

		/**
		 * @brief		初期生成
		 * @param[in]	t	使うテクスチャ
		 * @param[in]	s	使うシェーダー
		 */
		void Create(const TexturePtr t, const ShaderPtr s, const GLuint lineCount = 100) {
			//テクスチャ設定
			texture_ = t;
			//シェーダー登録
			shader_ = s;

			//サイズ
			GLuint size = (lineCount - 1) * 4;
			//ポリゴン用のデータ生成
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

			//頂点データ配列作成
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
		 * @brief		頂点情報の更新
		 */
		void RefreshVertex(const LineArray& lines) {
			//今までのデータ削除
			vertices.clear();

			//ラインの数不足
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
		 * @brief		スプライトを表示させる
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
		 * @brief		解放処理
		 */
		void Release() {
			if (vertexArrayID > 0)
			{
				glDeleteVertexArrays(1, &vertexArrayID);
				vertexArrayID = 0;
			}
		}

		/**
		 * @brief		Texture_へのAccessor
		 * @return		テクスチャ
		 */
		const TexturePtr Texture(void) const {
			return texture_;
		}

		/**
		 * @brief		Sampler_へのAccessor
		 * @return		サンプラ
		 */
		void Sampler(const SamplerPtr& v) noexcept { sampler_ = v; }
		/**
		 * @brief		Sampler_へのAccessor
		 * @return		サンプラ
		 */
		const SamplerPtr Sampler(void) const {
			return sampler_;
		}

		/**
		 * @brief		ShaderへのAccessor
		 * @return		シェーダー
		 */
		const ShaderPtr Shader(void) const {
			return shader_;
		}

	};
	using PolyLinePtr = std::shared_ptr< PolyLine >;
}