#pragma once

#include	"Sprite.h"

namespace Sample {

	class SpriteBatch {
	protected:
		/** 利用するシェーダー */
		ShaderPtr			shader_;

		/** 描画用バッファ */
		Buffer				vertexBuffer_;
		/** 描画用バッファ */
		Buffer				indexBuffer_;

		/** 頂点配列 */
		GLuint				vertexArrayID;

		/** 描画用頂点情報 */
		struct Vertex {
			glm::vec3		pos;
			glm::vec2		uv;
			glm::vec4		color;
		};
		/** 描画頂点配列 */
		std::vector<Vertex>	vertices;

		/**
		 * @brief		描画登録
		 */
		struct Register {
			/** 描画する数 */
			size_t			count;
			/** 利用するテクスチャ */
			TexturePtr		texture;
			/** 利用するサンプラ */
			SamplerPtr		sampler;
		};
		/** 描画テクスチャ配列 */
		std::vector<Register> renders;

		/** 描画テクスチャ登録 */
		void RegisterTexture(TexturePtr& texture)
		{
			//描画登録
			if (renders.empty())
			{
				renders.push_back({ 1, texture, SamplerPtr() });
			}
			else
			{
				Register& data = renders.back();
				if (data.texture == texture)
				{
					data.count++;
				}
				else
				{
					renders.push_back({ 1, texture, SamplerPtr() });
				}
			}
		}
		/** 頂点に座標登録 */
		void RegisterVertexPosition(Vertex* out, const Vector3F& pos, float tw, float th)
		{
			out[0].pos = glm::vec4(pos.x, -th - pos.y, pos.z, 1);
			out[1].pos = glm::vec4(tw + pos.x, -th - pos.y, pos.z, 1);
			out[2].pos = glm::vec4(pos.x, -pos.y, pos.z, 1);
			out[3].pos = glm::vec4(tw + pos.x, -pos.y, pos.z, 1);
		}
		/** 頂点に色登録 */
		void RegisterVertexColor(Vertex* out, const glm::vec4& color)
		{
			out[0].color = color;
			out[1].color = color;
			out[2].color = color;
			out[3].color = color;
		}
		/** 頂点に色登録 */
		void RegisterVertexColor(Vertex* out, const Vector4F& color)
		{
			RegisterVertexColor(out, glm::vec4(color.r, color.g, color.b, color.a));
		}
		/** 頂点にUV登録 */
		void RegisterVertexUV(Vertex* out, float lt, float rt, float ut, float bt)
		{
			out[0].uv[0] = lt;	out[0].uv[1] = bt;
			out[1].uv[0] = rt;	out[1].uv[1] = bt;
			out[2].uv[0] = lt;	out[2].uv[1] = ut;
			out[3].uv[0] = rt;	out[3].uv[1] = ut;
		}
	public:
		/**
		 * @brief		コンストラクタ
		 */
		SpriteBatch()
			: shader_()
			, vertexBuffer_()
			, indexBuffer_()
			, vertexArrayID(0)
			, vertices()
			, renders() {
		}
		SpriteBatch(const SpriteBatch& obj) = delete;

		/**
		 * @brief		デストラクタ
		 */
		~SpriteBatch() {
			Release();
		}

		/**
		 * @brief		初期生成
		 * @param[in]	s	使うシェーダー
		 */
		void Create(const ShaderPtr s, const GLuint polygonCount = 1000) {
			//シェーダー登録
			shader_ = s;

			//ポリゴン用のデータ生成
			vertices.resize(polygonCount * 4);
			vertexBuffer_.Create(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STREAM_DRAW);
			vertices.clear();

			std::vector<GLuint> idx;
			idx.resize(polygonCount * 6);
			for (GLuint i = 0; i < polygonCount; i++)
			{
				idx[i * 6 + 0] = (i * 4) + 0;
				idx[i * 6 + 1] = (i * 4) + 1;
				idx[i * 6 + 2] = (i * 4) + 2;
				idx[i * 6 + 3] = (i * 4) + 1;
				idx[i * 6 + 4] = (i * 4) + 3;
				idx[i * 6 + 5] = (i * 4) + 2;
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
		void RefreshVertex() {
			vertexBuffer_.SubData(0, sizeof(Vertex) * vertices.size(), vertices.data());
		}

		/**
		 * @brief		再登録用リセット
		 */
		void Reset() {
			vertices.clear();
			renders.clear();
		}

		/**
		 * @brief		テクスチャで登録
		 *				指定は座標のみ
		 * @param[in]	texture			利用するテクスチャ
		 * @param[in]	pos				描画座標
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos) {
			//追加で最大を超える
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "描画可能最大数を超過します...\n";
				return;
			}
			//頂点代入
			Vertex out[4];
			RegisterVertexPosition(out, pos, (float)texture->Width(), (float)texture->Height());
			RegisterVertexColor(out, glm::vec4(1));
			RegisterVertexUV(out, 0, 1, 0, 1);

			vertices.insert(vertices.end(), out, out + 4);

			//登録
			RegisterTexture(texture);
		}

		/**
		 * @brief		テクスチャで登録
		 *				指定は座標と色のみ
		 * @param[in]	texture			利用するテクスチャ
		 * @param[in]	pos				描画座標
		 * @param[in]	color			描画色
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos, const Vector4F& color) {
			//追加で最大を超える
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "描画可能最大数を超過します...\n";
				return;
			}
			//頂点代入
			Vertex out[4];
			RegisterVertexPosition(out, pos, (float)texture->Width(), (float)texture->Height());
			RegisterVertexColor(out, color);
			RegisterVertexUV(out, 0, 1, 0, 1);

			vertices.insert(vertices.end(), out, out + 4);

			//登録
			RegisterTexture(texture);
		}

		/**
		 * @brief		テクスチャで登録
		 *				指定は座標と色と矩形
		 * @param[in]	texture			利用するテクスチャ
		 * @param[in]	pos				描画座標
		 * @param[in]	color			描画色
		 * @param[in]	rect			描画矩形
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos, const Vector4F& color, const RectangleF& rect) {
			//追加で最大を超える
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "描画可能最大数を超過します...\n";
				return;
			}
			//頂点代入
			Vertex out[4];
			float tw = (float)texture->Width();
			float th = (float)texture->Height();
			RegisterVertexPosition(out, pos, rect.Width(), rect.Height());
			RegisterVertexColor(out, color);
			float lt = rect.Left / tw;
			float rt = rect.Right / tw;
			float ut = rect.Top / th;
			float bt = rect.Bottom / th;
			RegisterVertexUV(out, lt, rt, ut, bt);

			vertices.insert(vertices.end(), out, out + 4);

			//登録
			RegisterTexture(texture);
		}

		/**
		 * @brief		スプライトで登録
		 * @param[in]	sprite			利用するスプライト
		 */
		void RenderRegister(SpritePtr& sprite) {
			//追加で最大を超える
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "描画可能最大数を超過します...\n";
				return;
			}
			//画像
			TexturePtr texture = sprite->Texture();
			//ポリゴンデータ作成
			float tw = (float)texture->Width();
			float th = (float)texture->Height();
			//UV
			const RectangleF& rect = sprite->SrcRect();
			float lt = rect.Left / tw;
			float rt = rect.Right / tw;
			float ut = rect.Top / th;
			float bt = rect.Bottom / th;
			if (sprite->XFlip())
			{
				float tmp = rt;
				rt = lt;
				lt = tmp;
			}
			if (sprite->YFlip())
			{
				float tmp = bt;
				bt = ut;
				ut = tmp;
			}
			//位置
			const Vector3F& pivot = sprite->Pivot();
			float lx = pivot.x * -rect.Width();
			float rx = (1 - pivot.x) * rect.Width();
			float uy = pivot.y * rect.Height();
			float by = (1 - pivot.y) * -rect.Height();

			//変換行列計算
			const Vector3F& position = sprite->Position();
			const Vector3F& rotation = sprite->Rotation();
			const Vector3F& scale = sprite->Scale();
			const Vector3F& anchor = sprite->Anchor();
			float tx = GraphicsController::GetInstance().ScreenWidth() * anchor.x;
			float ty = GraphicsController::GetInstance().ScreenHeight() * anchor.y;
			const glm::mat4 matT = glm::translate(glm::mat4(1), glm::vec3(tx + position.x, -ty + -position.y, position.z));
			const glm::mat4 matRY = glm::rotate(matT, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			const glm::mat4 matRXY = glm::rotate(matRY, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			const glm::mat4 matRZXY = glm::rotate(matRXY, glm::radians(-rotation.z), glm::vec3(0, 0, 1));
			const glm::mat4 matS = glm::scale(matRZXY, glm::vec3(scale.x, scale.y, scale.z));

			//頂点代入
			Vertex out[4];
			const Vector3F* offset = sprite->VertexOffset();
			out[0].pos = matT * glm::vec4(lx + offset[0].x, by - offset[0].y, offset[0].z, 1);
			out[1].pos = matT * glm::vec4(rx + offset[1].x, by - offset[1].y, offset[1].z, 1);
			out[2].pos = matT * glm::vec4(lx + offset[2].x, uy - offset[2].y, offset[2].z, 1);
			out[3].pos = matT * glm::vec4(rx + offset[3].x, uy - offset[3].y, offset[3].z, 1);

			RegisterVertexColor(out, sprite->Color());
			RegisterVertexUV(out, lt, rt, ut, bt);

			vertices.insert(vertices.end(), out, out + 4);

			//登録
			RegisterTexture(texture);
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

			//登録テクスチャを一括描画
			size_t offset = 0;
			for (const auto& r : renders)
			{
				shader_->BindTexture(0, r.texture->ID());
				if (r.sampler)
				{
					shader_->BindSampler(0, r.sampler->ID());
				}
				glDrawElements(GL_TRIANGLES, r.count * 6, GL_UNSIGNED_INT,
					reinterpret_cast<const GLvoid*>(offset));
				offset += r.count * 6 * sizeof(GLuint);
			}
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
		 * @brief		ShaderへのAccessor
		 * @return		シェーダー
		 */
		const ShaderPtr Shader(void) const {
			return shader_;
		}

	};
	using SpriteBatchPtr = std::shared_ptr< SpriteBatch >;
}