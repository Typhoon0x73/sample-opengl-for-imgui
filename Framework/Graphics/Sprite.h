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
		/** スプライトの位置 */
		Vector3F	position_;
		/** スプライトの向き */
		Vector3F	rotation_;
		/** スプライトの大きさ */
		Vector3F	scale_;

		/** スプライトの描画行列 */
		glm::mat4	matModel_;

		/** アンカー */
		Vector3F	anchor_;
		/** ピボット */
		Vector3F	pivot_;
		/** 各頂点への補正値 */
		Vector3F	offset_[4];

		/** 色 */
		Vector4F	color_;

		/** 現在のアニメーション矩形 */
		RectangleF	srcRect_;

		/** 横反転フラグ */
		bool		xflip_;
		/** 縦反転フラグ */
		bool		yflip_;

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
		/** 頂点カラー */
		GLuint		colorLocation;

		/** 描画用頂点情報 */
		struct Vertex {
			float pos[3];
			float uv[2];
		};

		/**
		 * @brief			頂点情報を求める
		 * @param[in/out]	out	出力する頂点情報
		 */
		void GetVertex(Vertex* out) {
			//ポリゴンデータ作成
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
			//位置
			float lx = pivot_.x * -srcRect_.Width();
			float rx = (1 - pivot_.x) * srcRect_.Width();
			float uy = pivot_.y * srcRect_.Height();
			float by = (1 - pivot_.y) * -srcRect_.Height();
			//頂点代入
			out[0].pos[0] = lx + offset_[0].x;	out[0].pos[1] = by - offset_[0].y;	out[0].pos[2] = 0 + offset_[0].z;	out[0].uv[0] = lt;	out[0].uv[1] = bt;
			out[1].pos[0] = rx + offset_[1].x;	out[1].pos[1] = by - offset_[1].y;	out[1].pos[2] = 0 + offset_[1].z;	out[1].uv[0] = rt;	out[1].uv[1] = bt;
			out[2].pos[0] = lx + offset_[2].x;	out[2].pos[1] = uy - offset_[2].y;	out[2].pos[2] = 0 + offset_[2].z;	out[2].uv[0] = lt;	out[2].uv[1] = ut;
			out[3].pos[0] = rx + offset_[3].x;	out[3].pos[1] = uy - offset_[3].y;	out[3].pos[2] = 0 + offset_[3].z;	out[3].uv[0] = rt;	out[3].uv[1] = ut;
		}

	public:
		/**
		 * @brief		コンストラクタ
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
		 * @brief		コンストラクタ
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
		 * @brief		デストラクタ
		 */
		~Sprite() {
			Release();
		}

		/**
		 * @brief		初期生成
		 * @param[in]	t	使うテクスチャ
		 * @param[in]	s	使うシェーダー
		 */
		void Create(const TexturePtr t, const ShaderPtr s) {
			if (texture_ != t)
			{
				//素材設定
				texture_ = t;
				//矩形設定
				srcRect_.Left = 0;
				srcRect_.Right = static_cast<float>(texture_->Width());
				srcRect_.Top = 0;
				srcRect_.Bottom = static_cast<float>(texture_->Height());
			}
			shader_ = s;
			//頂点データを求める
			Vertex vx[4];
			GetVertex(vx);
			//ポリゴンデータ作成
			GLushort idx[4] = { 0,1,2,3 };
			vertexBuffer_.Create(GL_ARRAY_BUFFER, sizeof(vx), vx, GL_STREAM_DRAW);
			indexBuffer_.Create(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

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

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			colorLocation = shader_->GetUniformLocation("baseColor");
		}

		/**
		 * @brief		頂点情報の更新
		 */
		void RefreshVertex() {
			Vertex vx[4];
			GetVertex(vx);
			vertexBuffer_.SubData(0, sizeof(vx), vx);
		}

		/**
		 * @brief		行列の更新
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
		 * @brief		スプライトを表示させる
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
		 * @brief		posへのAccessor
		 * @param[in]	p	位置
		 */
		void Position(const Vector3F& p) { position_ = p; }
		/**
		 * @brief		posへのAccessor
		 * @return		位置
		 */
		const Vector3F& Position() const noexcept { return position_; }

		/**
		 * @brief		rotationへのAccessor
		 * @param[in]	p	向き
		 */
		void Rotation(const Vector3F& p) { rotation_ = p; }
		/**
		 * @brief		rotationへのAccessor
		 * @return		向き
		 */
		const Vector3F& Rotation() const noexcept { return rotation_; }

		/**
		 * @brief		scaleへのAccessor
		 * @param[in]	p	大きさ
		 */
		void Scale(const Vector3F& p) { scale_ = p; }
		/**
		 * @brief		scaleへのAccessor
		 * @return		大きさ
		 */
		const Vector3F& Scale() const noexcept { return scale_; }

		/**
		 * @brief		pivotへのAccessor
		 * @param[in]	p	ピボット
		 */
		void Pivot(const Vector3F& p) { pivot_ = p; }
		/**
		 * @brief		pivotへのAccessor
		 * @return		ピボット
		 */
		const Vector3F& Pivot() const noexcept { return pivot_; }

		/**
		 * @brief		anchorへのAccessor
		 * @param[in]	p	アンカー
		 */
		void Anchor(const Vector3F& p) { anchor_ = p; }
		/**
		 * @brief		anchorへのAccessor
		 * @return		アンカー
		 */
		const Vector3F& Anchor() const noexcept { return anchor_; }

		/**
		 * @brief		矩形取得
		 * @return		矩形
		 */
		const RectangleF& SrcRect() const {
			return srcRect_;
		}

		/**
		 * @brief		矩形設定
		 * @param[in]	矩形
		 */
		const void SrcRect(const RectangleF& r) {
			if (srcRect_ != r)
			{
				srcRect_ = r;
				RefreshVertex();
			}
		}

		/**
		 * @brief		color_へのAccessor
		 * @param[in]	アルファ値
		 */
		void Alpha(const float a) {
			color_.a = a;
		}

		/**
		 * @brief		color_へのAccessor
		 * @return		アルファ値
		 */
		const float Alpha(void) const {
			return color_.a;
		}

		/**
		 * @brief		color_へのAccessor
		 * @param[in]	c	色
		 */
		void Color(const Vector4F& c) { color_ = c; }
		/**
		 * @brief		color_へのAccessor
		 * @return		色
		 */
		const Vector4F& Color() const noexcept { return color_; }

		/**
		 * @brief		xflip_へのAccessor
		 * @param[in]	f	反転フラグ
		 */
		void XFlip(bool f)
		{
			xflip_ = f;
		}
		/**
		 * @brief		xflip_へのAccessor
		 * @return		反転フラグ
		 */
		const bool XFlip() const noexcept { return xflip_; }

		/**
		 * @brief		yflip_へのAccessor
		 * @param[in]	f	反転フラグ
		 */
		void YFlip(bool f)
		{
			yflip_ = f;
		}
		/**
		 * @brief		yflip_へのAccessor
		 * @return		反転フラグ
		 */
		const bool YFlip() const noexcept { return yflip_; }

		/**
		 * @brief		頂点オフセットへのAccessor
		 * @param[in]	n	オフセット番号
		 * @param[in]	p	オフセット位置
		 */
		void VertexOffset(const int n, const Vector3F& p) { offset_[n] = p; }
		/**
		 * @brief		頂点オフセットへのAccessor
		 * @return		頂点オフセット
		 */
		const Vector3F* VertexOffset() const noexcept { return offset_; }

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
	using SpritePtr = std::shared_ptr< Sprite >;
}